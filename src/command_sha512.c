/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha512.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 09:31:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 09:31:52 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"
#include <stdio.h>

int	command_sha512_fd(int fd, int print)
{
	t_sha512_ctx	ctx;
	uint8_t		digest[64];
	uint8_t		buf[4096];
	int		readed;

	sha512_init(&ctx);
	while ((readed = read(fd, buf, 4096)) > 0)
	{
		sha512_update(&ctx, buf, readed);
		if (print)
			readed = write(1, buf, readed);
	}
	if (readed == -1)
		return (0);
	sha512_final(digest, &ctx);
	for (int i = 0; i < 64; ++i)
		printf("%02x", digest[i]);
	printf("\n");
	return (1);
}

int	command_sha512_strings(int ac, char **av, int *i, int quiet, int reverse)
{
	++(*i);
	if (*i >= ac)
		return (0);
	(void)av;
	(void)quiet;
	(void)reverse;
	return (1);
}

int	command_sha512(int ac, char **av)
{
	int reverse;
	int quiet;
	int i;

	if (!ac)
		return (command_sha512_fd(0, 0));
	reverse = 0;
	quiet = 0;
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p"))
		{
			if (!command_sha512_fd(0, 1))
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-q"))
			quiet = 1;
		else if (!ft_strcmp(av[i], "-r"))
			reverse = 1;
		else if (!ft_strcmp(av[i], "-s"))
			if (!command_sha512_strings(ac, av, &i, quiet, reverse))
				return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
