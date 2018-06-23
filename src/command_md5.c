/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:26:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/23 20:56:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include <stdio.h>

int	command_md5_fd(int fd, int print)
{
	t_md5_ctx	ctx;
	uint8_t		digest[16];
	uint8_t		buf[4096];
	int		readed;

	md5_init(&ctx);
	while ((readed = read(fd, buf, 4096)) > 0)
	{
		md5_update(&ctx, buf, readed);
		if (print)
			readed = write(1, buf, readed);
	}
	if (readed == -1)
		return (0);
	md5_final(digest, &ctx);
	for (int i = 0; i < 16; ++i)
		printf("%x", digest[i]);
	printf("\n");
	return (1);
}

int	command_md5_strings(int ac, char **av, int *i, int quiet, int reverse)
{
	++(*i);
	if (*i >= ac)
		return (0);
	(void)av;
	(void)quiet;
	(void)reverse;
	return (1);
}

int	command_md5(int ac, char **av)
{
	int reverse;
	int quiet;
	int i;

	if (!ac)
		return (command_md5_fd(0, 0));
	reverse = 0;
	quiet = 0;
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p"))
		{
			if (!command_md5_fd(0, 1))
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-q"))
			quiet = 1;
		else if (!ft_strcmp(av[i], "-r"))
			reverse = 1;
		else if (!ft_strcmp(av[i], "-s"))
			if (!command_md5_strings(ac, av, &i, quiet, reverse))
				return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
