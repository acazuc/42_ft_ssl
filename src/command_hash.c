/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:45:55 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 15:00:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <errno.h>
#include <fcntl.h>

static int	command_hash_fd(t_hash_data *data, int fd, int print, char *fn)
{
	uint8_t		*digest;
	char		*hash;
	uint8_t		buf[4096];
	int		readed;

	if (!data->h.h->init(data->h.ctx))
		return (0);
	while ((readed = read(fd, buf, 4096)) > 0)
	{
		if (!data->h.h->update(data->h.ctx, buf, readed))
			return (0);
		if (print)
			readed = write(1, buf, readed);
	}
	if (readed == -1)
		return (0);
	if (!(digest = malloc(sizeof(*digest) * data->h.h->digest_len)))
		return (0);
	if (!data->h.h->final(digest, data->h.ctx))
		return (0);
	if (!(hash = malloc(sizeof(*hash) * (data->h.h->digest_len * 2 + 1))))
		return (0);
	bin2hex(hash, digest, data->h.h->digest_len);
	free(digest);
	hash[data->h.h->digest_len * 2] = 0;
	if (!print && !data->quiet && !data->reverse)
	{
		ft_putstr(data->h.h->name);
		ft_putstr(" (");
		ft_putstr(fn);
		ft_putstr(") = ");
	}
	ft_putstr(hash);
	if (!print && !data->quiet && data->reverse)
	{
		ft_putstr(" ");
		ft_putstr(fn);
	}
	ft_putchar('\n');
	free(hash);
	return (1);
}

static int	command_hash_string(t_hash_data *data, int ac, char **av
		, int *i)
{
	uint8_t		*digest;
	char		*hash;

	if ((*i)++ >= ac)
	{
		ft_putendl_fd("ft_ssl: you must specify a string to hash", 2);
		return (0);
	}
	if (!data->h.h->init(data->h.ctx))
		return (0);
	if (!data->h.h->update(data->h.ctx, (const uint8_t*)av[*i]
				, strlen(av[*i])))
		return (0);
	if (!(digest = malloc(sizeof(*digest) * data->h.h->digest_len)))
		return (0);
	if (!data->h.h->final(digest, data->h.ctx))
		return (0);
	if (!(hash = malloc(sizeof(*hash) * (data->h.h->digest_len * 2 + 1))))
		return (0);
	bin2hex(hash, digest, data->h.h->digest_len);
	free(digest);
	hash[data->h.h->digest_len * 2] = 0;
	if (!data->quiet && !data->reverse)
	{
		ft_putstr(data->h.h->name);
		ft_putstr(" (\"");
		ft_putstr(av[*i]);
		ft_putstr("\") = ");
	}
	ft_putstr(hash);
	if (!data->quiet && data->reverse)
	{
		ft_putstr(" \"");
		ft_putstr(av[*i]);
		ft_putstr("\"");
	}
	ft_putchar('\n');
	free(hash);
	return (1);
}

static int	command_hash_file(t_hash_data *data, char *file)
{
	int	ret;
	int	fd;

	ret = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr_fd("ft_ssl: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": failed to open file", 2);
		return (0);
	}
	if (!(ret = command_hash_fd(data, fd, 0, file)))
	{
		ft_putstr_fd("ft_ssl: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": failed to read file", 2);
		ret = 0;
	}
	close(fd);
	return (ret);
}

static int	command_hash_files(t_hash_data *data, int ac, char **av, int *i)
{
	int	ret;

	ret = 1;
	while (*i < ac)
	{
		if (!command_hash_file(data, av[*i]))
			ret = 0;
		++(*i);
	}
	return (ret);
}

int	command_hash(int ac, char **av, t_hash_data *data)
{
	int	written;
	int	err;
	int	i;

	data->reverse = 0;
	data->quiet = 0;
	written = 0;
	if (!ac)
		return (command_hash_fd(data, 0, 0, "stdin"));
	err = 0;
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p"))
		{
			err |= !command_hash_fd(data, 0, 1, "stdin");
			written = 1;
		}
		else if (!ft_strcmp(av[i], "-q"))
			data->quiet = 1;
		else if (!ft_strcmp(av[i], "-r"))
			data->reverse = 1;
		else if (!ft_strcmp(av[i], "-s"))
		{
			err |= !command_hash_string(data, ac, av, &i);
			written = 1;
		}
		else
		{
			err |= !command_hash_files(data, ac, av, &i);
			written = 1;
		}
		++i;
	}
	if (!written)
		return (command_hash_fd(data, 0, 0, "stdin"));
	return (err ? EXIT_FAILURE : EXIT_SUCCESS);
}
