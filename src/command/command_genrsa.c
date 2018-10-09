/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/09 14:41:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "ft_ssl.h"
#include "rsa.h"
#include "pem.h"
#include <fcntl.h>

static int	do_init(t_genrsa_data *data)
{
	ft_memset(data, 0, sizeof(data));
	data->exp = 0x10001;
	data->crypt_method = NULL;
	data->fdout = 1;
	data->key_len = 512;
	if (!bignum_rand_add_urandom())
	{
		ft_putendl_fd("ft_ssl: failed to init rng", 2);
		return (0);
	}
	return (1);
}

static int	handle_out(t_genrsa_data *data, int ac, char **av, int *i)
{
	++(*i);
	if (*i >= ac)
	{
		ft_putendl_fd("ft_ssl: expected file after -out", 2);
		return (0);
	}
	if (data->fdout != 1)
		close(data->fdout);
	if ((data->fdout = open(av[*i], O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		ft_putstr_fd("ft_ssl: failed to open file: ", 2);
		ft_putendl_fd(av[*i], 2);
		return (0);
	}
	return (1);
}

static int	parse_args(t_genrsa_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-out"))
		{
			if (!handle_out(data, ac, av, &i))
				return (0);
		}
		else if (!ft_strcmp(av[i], "-f4") || !ft_strcmp(av[i], "-F4"))
			data->exp = 0x10001;
		else if (!ft_strcmp(av[i], "-3"))
			data->exp = 3;
		else if (!ft_strcmp(av[i], "-des"))
			data->crypt_method = "DES-CBC";
		else if (!ft_strcmp(av[i], "-des2"))
			data->crypt_method = "DES-EDE-CBC";
		else if (!ft_strcmp(av[i], "-des3"))
			data->crypt_method = "DES-EDE3-CBC";
		else if (!ft_strcmp(av[i], "-aes128"))
			data->crypt_method = "AES-128-CBC";
		else if (!ft_strcmp(av[i], "-aes192"))
			data->crypt_method = "AES-192-CBC";
		else if (!ft_strcmp(av[i], "-aes256"))
			data->crypt_method = "AES-256-CBC";
		else if (!ft_strcmp(av[i], "-camellia128"))
			data->crypt_method = "CAMELLIA-128-CBC";
		else if (!ft_strcmp(av[i], "-camellia192"))
			data->crypt_method = "CAMELLIA-192-CBC";
		else if (!ft_strcmp(av[i], "-camellia256"))
			data->crypt_method = "CAMELLIA-256-CBC";
		else if (!ft_strcmp(av[i], "-passout"))
		{
		}
		else if (ft_strisdigit(av[i]))
			data->key_len = ft_atol(av[i]);
		else
		{
			ft_putstr_fd("ft_ssl: invalid argument: ", 2);
			ft_putendl_fd(av[i], 2);
			return (0);
		}
		++i;
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
	a = bignum_new();
	bignum_dec2bignum(a, "112233445566778899112233445566778899887766554433211");
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

	if (!do_init(&data))
		return (EXIT_FAILURE);
	if (!parse_args(&data, ac, av))
		return (EXIT_FAILURE);
	if (data.key_len < 16)
	{
		ft_putendl_fd("ft_ssl: invalid key length, minimum is 16", 2);
		return (EXIT_FAILURE);
	}
	if (!rsa_genkey(&data.rsa_ctx, data.key_len, data.exp, 1))
	{
		ft_putendl_fd("ft_ssl: failed to generate key", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr("e is ");
	bignum_print(data.rsa_ctx.e);
	ft_putstr(" (0x");
	bignum_printhex(data.rsa_ctx.e);
	ft_putendl(")");
	if (!pem_print_rsa_priv(&data.rsa_ctx, data.fdout, data.crypt_method))
	{
		ft_putendl_fd("ft_ssl: failed to write PEM key", 2);
		return (EXIT_FAILURE);
	}
	run_test(&data);
	rsa_free(&data.rsa_ctx);
	return (1);
}
