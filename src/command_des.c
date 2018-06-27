/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:25:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/27 18:27:34 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"
#include "sha512.h"
#include <fcntl.h>
#include <stdio.h>

static int	file_open(int ac, char **av, int *i, int type)
{
	(*i)++;
	if (*i >= ac)
		return (-1);
	if (type)
		return (open(av[*i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (open(av[*i], O_RDONLY));
}

int		command_des(int ac, char **av)
{
	t_pbkdf2_ctx	hctx;
	t_sha512_ctx	hhctx;

	hctx.h.h = &g_hash_sha512;
	hctx.h.ctx = &hhctx;
	hctx.salt = (uint8_t*)"salt";
	hctx.salt_len = 4;
	hctx.password = (uint8_t*)"password";
	hctx.password_len = 8;
	hctx.iterations = 1024;
	uint8_t out[500];
	char tmp[1001];
	hctx.out = out;
	hctx.out_len = 500;
	pbkdf2(&hctx);
	bin2hex(tmp, out, 500);
	tmp[1000] = 0;
	ft_putendl(tmp);
	return (EXIT_SUCCESS);
	t_des_ctx	ctx;
	uint64_t	val;

	ctx.mode = 1;
	des_generate_keys(&ctx, 0b0001001100110100010101110111100110011011101111001101111111110001);
	//val = 0b0000000100100011010001010110011110001001101010111100110111101111;
	val = 0b1000010111101000000100110101010000001111000010101011010000000101;
	val = des_operate_block(&ctx, val);
	printf("%lx\n", val);
	(void)ac;
	(void)av;
	char	*init_vector;
	char	*password;
	char	*salt;
	char	*key;
	int	fdout;
	int	fdin;
	int	mode;
	int	b64;
	int	i;

	init_vector = NULL;
	password = NULL;
	salt = NULL;
	key = NULL;
	fdout = 1;
	fdin = 0;
	mode = 0;
	b64 = 0;
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-e"))
			mode = 0;
		else if (!ft_strcmp(av[i], "-d"))
			mode = 1;
		else if (!ft_strcmp(av[i], "-a"))
			b64 = 1;
		else if (!ft_strcmp(av[i], "-i"))
		{
			if (fdin != 0)
				close(fdin);
			if ((fdin = file_open(ac, av, &i, 0)) == -1)
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-o"))
		{
			if (fdout != 1)
				close(fdout);
			if ((fdout = file_open(ac, av, &i, 1)) == -1)
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-k"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected key after -k", 2);
				return (EXIT_FAILURE);
			}
			key = ft_strdup(av[i]);
		}
		else if (!ft_strcmp(av[i], "-p"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected password after -p", 2);
				return (EXIT_FAILURE);
			}
			password = ft_strdup(av[i]);
		}
		else if (!ft_strcmp(av[i], "-s"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected salt after -s", 2);
				return (EXIT_FAILURE);
			}
			salt = ft_strdup(av[i]);
		}
		else if (ft_strcmp(av[i], "-v"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected init vector after -v", 2);
				return (EXIT_FAILURE);
			}
			init_vector = ft_strdup(av[i]);
		}
		++i;
	}
	if (!key)
	{
		if (!password)
		{
			if (!(password = getpass("Enter des password: ")))
				return (EXIT_FAILURE);
		}
		if (!salt)
		{
			if (!(salt = malloc(8)))
				return (EXIT_FAILURE);
			if (!random_bytes((uint8_t*)salt, 8))
				return (EXIT_FAILURE);
		}
		//if (!(key = pbkdf2(password, salt, 4096, 8)))
		//	return (EXIT_FAILURE);
	}
	(void)b64;
	(void)mode;
	(void)init_vector;
	//start cipher
	return (EXIT_SUCCESS);
}
