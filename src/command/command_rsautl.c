/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 21:28:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 12:58:32 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

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
	if (!cmd_rsautl_args(data, ac, av))
		return (0);
	if (!check_params(data))
		return (0);
	return (1);
}

int			command_rsautl(int ac, char **av)
{
	t_rsautl_data	data;

	if (!do_init(&data, ac, av))
		return (EXIT_FAILURE);
	if (data.pubin)
	{
		if (!pem_read_rsa_pub_file(&data.rsa_ctx, data.keyfd, data.passin))
			return (0);
	}
	else
	{
		if (!pem_read_rsa_priv_file(&data.rsa_ctx, data.keyfd, data.passin))
			return (0);
	}
	return (EXIT_SUCCESS);
}
