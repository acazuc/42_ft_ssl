/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:38:49 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 13:12:28 by acazuc           ###   ########.fr       */
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
	data->cipher_name = NULL;
	if (!cmd_rsa_args(data, ac, av))
		return (0);
	if (data->pubin)
		data->pubout = 1;
	return (1);
}

int			command_rsa(int ac, char **av)
{
	t_rsa_data	data;

	if (!do_init(&data, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_rsa_read(&data))
		return (EXIT_FAILURE);
	if (data.print_text)
		cmd_rsa_print_text(&data);
	if (data.print_modulus)
	{
		ft_putstr("Modulus=");
		bignum_printhex(data.rsa_ctx.n);
	}
	if (!data.noout && !cmd_rsa_write(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
