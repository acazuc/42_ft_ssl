/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:26:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"
#include "pem.h"
#include <fcntl.h>

static int	do_init(t_genrsa_data *data)
{
	ft_memset(data, 0, sizeof(data));
	data->exp = 0x10001;
	data->crypt_method = 0;
	data->fdout = 1;
	if (!base64_write_init(&data->b64_ctx))
	{
		ft_putendl_fd("ft_ssl: failed to init b64_write", 2);
		return (0);
	}
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
			data->crypt_method = 1;
		else if (!ft_strcmp(av[i], "-des2"))
			data->crypt_method = 2;
		else if (!ft_strcmp(av[i], "-des3"))
			data->crypt_method = 3;
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

int	command_genrsa(int ac, char **av)
{
	t_genrsa_data	data;

	if (!do_init(&data))
		return (EXIT_FAILURE);
	if (!parse_args(&data, ac, av))
		return (EXIT_FAILURE);
	data.b64_ctx.fdout = data.fdout;
	if (data.key_len < 16)
	{
		ft_putendl_fd("ft_ssl: invalid key len, minimum is 16", 2);
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
	char *dataa;
	int len;
	if ((len = pem_write_rsa_priv(&dataa, &data.rsa_ctx)) == -1)
	{
		ft_putendl_fd("ft_ssl: failed to generate pem file", 2);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", data.fdout);
	base64_write_update(&data.b64_ctx, (uint8_t*)dataa, len);
	base64_write_final(&data.b64_ctx);
	ft_putendl_fd("-----END RSA PRIVATE KEY-----", data.fdout);
	free(dataa);


	ft_putstr("n: ");
	bignum_print(data.rsa_ctx.n);
	ft_putstr(" (");
	ft_putul(data.rsa_ctx.n->len * 4);
	ft_putstr(")\n");
	ft_putstr("p: ");
	bignum_print(data.rsa_ctx.p);
	ft_putstr(" (");
	ft_putul(data.rsa_ctx.p->len * 4);
	ft_putstr(")\n");
	ft_putstr("q: ");
	bignum_print(data.rsa_ctx.q);
	ft_putstr(" (");
	ft_putul(data.rsa_ctx.q->len * 4);
	ft_putstr(")\n");
	ft_putstr("d: ");
	bignum_print(data.rsa_ctx.d);
	ft_putstr(" (");
	ft_putul(data.rsa_ctx.d->len * 4);
	ft_putstr(")\n");
	t_bignum *a = bignum_new();
	bignum_dec2bignum(a, "112233445566778899112233445566778899887766554433211");
	rsa_encrypt(&data.rsa_ctx, a, a);
	ft_putstr("Crypted: ");
	bignum_print(a);
	ft_putchar('\n');
	rsa_decrypt(&data.rsa_ctx, a, a);
	ft_putstr("Decrypted: ");
	bignum_print(a);
	ft_putchar('\n');
	rsa_free(&data.rsa_ctx);
	return (1);
}
