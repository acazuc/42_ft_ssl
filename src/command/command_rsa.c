/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:38:49 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/17 20:50:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_init(t_rsa_data *data, int ac, char **av)
{
	data->inform = RSA_FORMAT_PEM;
	data->outform = RSA_FORMAT_PEM;
	data->passin = NULL;
	data->passout = NULL;
	data->fdin = 0;
	data->fdout = 1;
	data->pubin = 0;
	data->pubout = 0;
	data->print_text = 0;
	data->print_modulus = 0;
	data->noout = 0;
	data->check = 0;
	data->cipher_name = NULL;
	ft_memset(&data->rsa_ctx, 0, sizeof(data->rsa_ctx));
	if (!cmd_rsa_args(data, ac, av))
		return (0);
	if (data->pubin)
		data->pubout = 1;
	return (1);
}

static int	do_clear(t_rsa_data *data, int ret)
{
	rsa_free(&data->rsa_ctx);
	return (ret);
}

int			command_rsa(int ac, char **av)
{
	t_rsa_data	data;

	if (!do_init(&data, ac, av))
		return (do_clear(&data, EXIT_FAILURE));
	if (!cmd_rsa_read(&data))
	{
		ft_putendl_fd("ft_ssl: invalid key", 2);
		return (do_clear(&data, EXIT_FAILURE));
	}
	if (data.check)
		cmd_rsa_check(&data);
	if (data.print_text)
		cmd_rsa_print_text(&data);
	if (data.print_modulus)
	{
		ft_putstr("Modulus=");
		bignum_printhex(data.rsa_ctx.n);
	}
	if (!data.noout && !cmd_rsa_write(&data))
	{
		ft_putendl_fd("ft_ssl: failed to write PEM key", 2);
		return (do_clear(&data, EXIT_FAILURE));
	}
	return (do_clear(&data, EXIT_SUCCESS));
}
