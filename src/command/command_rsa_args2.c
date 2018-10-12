/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa_args2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 11:28:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 11:54:32 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

int	cmd_rsa_handle_inform_outform(t_rsa_data *data, int ac, char **av
		, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putstr_fd("ft_ssl: format expected after ", 2);
		ft_putendl_fd(av[*i], 2);
		return (0);
	}
	if (ft_strcmp(av[*i + 1], "PEM"))
	{
		ft_putstr_fd("ft_ssl: unsupported format: ", 2);
		ft_putendl_fd(av[*i + 1], 2);
		return (0);
	}
	if (!ft_strcmp(av[*i], "-inform"))
		data->inform = RSA_FORMAT_PEM;
	else
		data->outform = RSA_FORMAT_PEM;
	(*i)++;
	return (1);
}

int	cmd_rsa_handle_passin_passout(t_rsa_data *data, int ac, char **av
		, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putstr_fd("ft_ssl: password expected after ", 2);
		ft_putendl_fd(av[*i], 2);
		return (0);
	}
	if (!ft_strcmp(av[*i], "-passin"))
		data->passin = av[*i + 1];
	else
		data->passout = av[*i + 1];
	(*i)++;
	return (1);
}

int	cmd_rsa_handle_in(t_rsa_data *data, int ac, char **av, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putstr_fd("ft_ssl: file expected after ", 2);
		ft_putendl_fd(av[*i], 2);
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

int	cmd_rsa_handle_out(t_rsa_data *data, int ac, char **av, int *i)
{
	if (*i + 1 >= ac)
	{
		ft_putstr_fd("ft_ssl: file expected after ", 2);
		ft_putendl_fd(av[*i], 2);
		return (0);
	}
	if (data->fdout != 1)
		close(data->fdout);
	if ((data->fdout = open(av[*i + 1], O_WRONLY | O_CREAT | O_TRUNC
					, 0644)) == -1)
	{
		ft_putstr_fd("ft_ssl: failed to open ", 2);
		ft_putendl_fd(av[*i + 1], 2);
		return (0);
	}
	(*i)++;
	return (1);
}
