/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:30:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 14:09:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include <stdio.h>
#include <fcntl.h>

static void	callback(uint8_t *data, size_t len, void *userptr)
{
	t_b64e_data	*ptr;
	int		osef;
	int		tmp;
	
	ptr = (t_b64e_data*)userptr;
	while (ptr->count + len >= 64)
	{
		tmp = 64 - ptr->count;
		if (tmp > 64)
			tmp = 64;
		osef = write(ptr->fd, data, tmp);
		data += tmp;
		len -= tmp;
		ptr->count = 0;
		ft_putchar('\n');
	}
	ptr->count += len;
	osef = write(ptr->fd, data, len);
	(void)osef;
}

static int	encode(int fdin, int fdout)
{
	t_b64e_data	data;
	t_b64e_ctx	ctx;
	uint8_t		buffer[4096];
	int		readed;

	data.fd = fdout;
	data.count = 0;
	if (!b64e_init(&ctx, callback, &data))
		return (EXIT_FAILURE);
	while ((readed = read(fdin, buffer, 4096)) > 0)
	{
		if (!b64e_update(&ctx, buffer, readed))
			return (EXIT_FAILURE);
	}
	if (readed < 0)
		return (EXIT_FAILURE);
	if (!b64e_finish(&ctx))
		return (EXIT_FAILURE);
	if (data.count)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

static int	decode(int fdin, int fdout)
{
	t_b64d_data	data;
	t_b64d_ctx	ctx;
	uint8_t		buffer[4096];
	int		readed;

	data.fd = fdout;
	if (!b64d_init(&ctx, callback, &data))
		return (EXIT_FAILURE);
	while ((readed = read(fdin, buffer, 4096)) > 0)
	{
		if (!b64d_update(&ctx, buffer, readed))
			return (EXIT_FAILURE);
	}
	if (readed < 0)
		return (EXIT_FAILURE);
	if (!b64d_finish(&ctx))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	file_open(int ac, char **av, int *i, int type)
{
	(*i)++;
	if (*i >= ac)
		return (-1);
	if (type)
		return (open(av[*i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (open(av[*i], O_RDONLY));
}

int		command_base64(int ac, char **av)
{
	int	fdout;
	int	fdin;
	int	mode;
	int	i;

	mode = 0;
	i = 0;
	fdin = 0;
	fdout = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-e"))
			mode = 0;
		else if (!ft_strcmp(av[i], "-d"))
			mode = 1;
		else if (!ft_strcmp(av[i], "-i"))
			fdin = file_open(ac, av, &i, 0);
		else if (!ft_strcmp(av[i], "-o"))
			fdout = file_open(ac, av, &i, 1);
		++i;
	}
	if (mode)
		return (decode(fdin, fdout));
	return (encode(fdin, fdout));
}