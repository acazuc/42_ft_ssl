/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 11:24:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"
#include "pem.h"

static int	do_init(t_genrsa_data *data, int ac, char **av)
{
	ft_memset(data, 0, sizeof(data));
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

static void	run_test(t_genrsa_data *data)
{
	t_bignum	*a;

	ft_putstr("n: ");
	bignum_print(data->rsa_ctx.n);
	ft_putstr(" (");
	ft_putul(bignum_num_bits(data->rsa_ctx.n));
	ft_putstr(")\n");
	ft_putstr("p: ");
	bignum_print(data->rsa_ctx.p);
	ft_putstr(" (");
	ft_putul(bignum_num_bits(data->rsa_ctx.p));
	ft_putstr(")\n");
	ft_putstr("q: ");
	bignum_print(data->rsa_ctx.q);
	ft_putstr(" (");
	ft_putul(bignum_num_bits(data->rsa_ctx.q));
	ft_putstr(")\n");
	ft_putstr("d: ");
	bignum_print(data->rsa_ctx.d);
	ft_putstr(" (");
	ft_putul(bignum_num_bits(data->rsa_ctx.d));
	ft_putstr(")\n");
	ft_putstr("phi: ");
	bignum_print(data->rsa_ctx.phi);
	ft_putstr(" (");
	ft_putul(bignum_num_bits(data->rsa_ctx.phi));
	ft_putstr(")\n");
	a = bignum_new();
	bignum_dec2bignum(a, "1122334455667788991122334455667788998877665544332");
	if (!rsa_enc(&data->rsa_ctx, a, a))
	{
		ft_putendl("rsa_encrypt() failed");
	}
	else
	{
		ft_putstr("Crypted: ");
		bignum_print(a);
		ft_putchar('\n');
		if (!rsa_dec(&data->rsa_ctx, a, a))
		{
			ft_putendl("rsa_decrypt() failed");
		}
		else
		{
			ft_putstr("Decrypted: ");
			bignum_print(a);
			ft_putchar('\n');
		}
	}
	bignum_free(a);
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
	run_test(&data);
	rsa_free(&data.rsa_ctx);
	return (1);
}
