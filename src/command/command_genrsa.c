/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 16:11:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"
#include "pem.h"

static int	do_init(t_genrsa_data *data, int ac, char **av)
{
	ft_memset(data, 0, sizeof(*data));
	data->exp = 0x10001;
	data->cipher_name = NULL;
	data->fdout = 1;
	data->key_len = 512;
	if (!bignum_rand_add_urandom())
	{
		ft_putendl_fd("ft_ssl: failed to init rng", 2);
		return (0);
	}
	if (!cmd_genrsa_parse_args(data, ac, av))
		return (0);
	if (data->key_len < 16)
	{
		ft_putendl_fd("ft_ssl: invalid key length, minimum is 16", 2);
		return (0);
	}
	return (1);
}

int			command_genrsa(int ac, char **av)
{
	t_genrsa_data	data;

	if (!do_init(&data, ac, av))
		return (EXIT_FAILURE);
	if (!rsa_genkey(&data.rsa_ctx, data.key_len, data.exp, 1))
	{
		ft_putendl_fd("ft_ssl: failed to generate key", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd("e is ", 2);
	bignum_print_fd(data.rsa_ctx.e, 2);
	ft_putstr_fd(" (0x", 2);
	bignum_printhex_fd(data.rsa_ctx.e, 2);
	ft_putendl_fd(")", 2);
	if (!pem_write_rsa_priv_file(&data.rsa_ctx, data.fdout
				, data.cipher_name, data.passout))
	{
		rsa_free(&data.rsa_ctx);
		ft_putendl_fd("ft_ssl: failed to write PEM key", 2);
		return (EXIT_FAILURE);
	}
	rsa_free(&data.rsa_ctx);
	return (EXIT_SUCCESS);
}
