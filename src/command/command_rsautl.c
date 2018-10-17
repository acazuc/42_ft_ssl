/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 21:28:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/17 20:48:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	check_params(t_rsautl_data *data)
{
	if (data->mode == -1)
	{
		ft_putendl_fd("ft_ssl: you must specify either -encrypt, -decrypt"
				", -sign or -verify", 2);
		return (0);
	}
	if (data->keyfd == -1)
	{
		ft_putendl_fd("ft_ssl: you must specify a key file with -inkey", 2);
		return (0);
	}
	if (data->pubin && data->mode == RSAUTL_MODE_DECRYPT)
	{
		ft_putendl_fd("ft_ssl: RSA decrypt mode require private key", 2);
		return (0);
	}
	if (data->pubin && data->mode == RSAUTL_MODE_SIGN)
	{
		ft_putendl_fd("ft_ssl: RSA sign mode require private key", 2);
		return (0);
	}
	return (1);
}

static int	do_init(t_rsautl_data *data, int ac, char **av)
{
	data->fdin = 0;
	data->fdout = 1;
	data->keyfd = -1;
	data->pubin = 0;
	data->mode = -1;
	data->hexdump = 0;
	data->passin = NULL;
	data->bignum = NULL;
	ft_memset(&data->rsa_ctx, 0, sizeof(data->rsa_ctx));
	if (!cmd_rsautl_args(data, ac, av))
		return (0);
	if (!check_params(data))
		return (0);
	return (1);
}

static int	do_clear(t_rsautl_data *data, int ret)
{
	if (data->fdin != 0)
		close(data->fdin);
	if (data->fdout != 1)
		close(data->fdout);
	close(data->keyfd);
	bignum_free(data->bignum);
	rsa_free(&data->rsa_ctx);
	return (ret);
}

static int	do_op(t_rsautl_data *data)
{
	if (data->mode == RSAUTL_MODE_ENCRYPT)
	{
		if (!rsa_enc(&data->rsa_ctx, data->bignum, data->bignum))
			return (0);
	}
	else if (data->mode == RSAUTL_MODE_DECRYPT)
	{
		if (!rsa_dec(&data->rsa_ctx, data->bignum, data->bignum))
			return (0);
	}
	else if (data->mode == RSAUTL_MODE_SIGN)
	{
		if (!rsa_sign(&data->rsa_ctx, data->bignum, data->bignum))
			return (0);
	}
	else if (data->mode == RSAUTL_MODE_VERIFY)
	{
		if (!rsa_verify(&data->rsa_ctx, data->bignum, data->bignum))
			return (0);
	}
	return (1);
}

int			command_rsautl(int ac, char **av)
{
	t_rsautl_data	data;

	if (!do_init(&data, ac, av))
		return (do_clear(&data, EXIT_FAILURE));
	if (!cmd_rsautl_readkey(&data))
	{
		ft_putendl_fd("ft_ssl: invalid key", 2);
		return (do_clear(&data, EXIT_FAILURE));
	}
	if (!cmd_rsautl_read(&data))
		return (do_clear(&data, EXIT_FAILURE));
	if (!do_op(&data))
	{
		ft_putendl_fd("ft_ssl: rsa operation failed", 2);
		return (do_clear(&data, EXIT_FAILURE));
	}
	if (!cmd_rsautl_write(&data))
		return (do_clear(&data, EXIT_FAILURE));
	return (do_clear(&data, EXIT_SUCCESS));
}
