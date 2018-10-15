/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl_args2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 11:52:15 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 12:23:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

int	cmd_rsautl_handle_passin(t_rsautl_data *data, int ac, char **av, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: expected password after -passin", 2);
		return (0);
	}
	data->passin = av[*i + 1];
	(*i)++;
	return (1);
}

int	cmd_rsautl_handle_inkey(t_rsautl_data *data, int ac, char **av, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: expected key file after -inkey", 2);
		return (0);
	}
	if ((data->keyfd = open(av[*i + 1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("ft_ssl: failed to open ", 2);
		ft_putendl_fd(av[*i + 1], 2);
		return (0);
	}
	(*i)++;
	return (1);
}

int	cmd_rsautl_handle_in(t_rsautl_data *data, int ac, char **av, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: expected file after -in", 2);
		return (0);
	}
	if (data->fdin != 0)
		close(data->fdin);
	if ((data->fdin = open(av[*i + 1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("ft_ssl: failed to open ", 2);
		ft_putendl_fd(av[*i + 1], 2);
		return (0);
	}
	(*i)++;
	return (1);
}

int	cmd_rsautl_handle_out(t_rsautl_data *data, int ac, char **av, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: expected file after -out", 2);
		return (0);
	}
	if (data->fdout != 0)
		close(data->fdout);
	if ((data->fdout = open(av[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644))
			== -1)
	{
		ft_putstr_fd("ft_ssl: failed to open ", 2);
		ft_putendl_fd(av[*i + 1], 2);
		return (0);
	}
	(*i)++;
	return (1);
}
