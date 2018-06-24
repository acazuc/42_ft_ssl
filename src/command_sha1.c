/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:27:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 14:13:49 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha1.h"

int	command_sha1_fd(int fd, int print)
{
	t_sha1_ctx	ctx;
	uint8_t		digest[20];
	uint8_t		buf[4096];
	char		hash[41];
	int		readed;

	if (!sha1_init(&ctx))
		return (0);
	while ((readed = read(fd, buf, 4096)) > 0)
	{
		if (!sha1_update(&ctx, buf, readed))
			return (0);
		if (print)
			readed = write(1, buf, readed);
	}
	if (readed == -1)
		return (0);
	if (!sha1_final(digest, &ctx))
		return (0);
	bin2hex(hash, digest, 20);
	hash[40] = 0;
	ft_putendl(hash);
	return (1);
}

int	command_sha1_strings(int ac, char **av, int *i, int quiet, int reverse)
{
	++(*i);
	if (*i >= ac)
		return (0);
	(void)av;
	(void)quiet;
	(void)reverse;
	return (1);
}

int	command_sha1(int ac, char **av)
{
	int reverse;
	int quiet;
	int i;

	if (!ac)
		return (command_sha1_fd(0, 0));
	reverse = 0;
	quiet = 0;
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p"))
		{
			if (!command_sha1_fd(0, 1))
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-q"))
			quiet = 1;
		else if (!ft_strcmp(av[i], "-r"))
			reverse = 1;
		else if (!ft_strcmp(av[i], "-s"))
			if (!command_sha1_strings(ac, av, &i, quiet, reverse))
				return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
