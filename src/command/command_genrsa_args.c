/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:57:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 13:19:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

static int	handle_out(t_genrsa_data *data, int ac, char **av, int *i)
{
	++(*i);
	if (*i >= ac)
	{
		ft_putendl_fd("ft_ssl: file expected after -out", 2);
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

static int	cmd_genrsa_parse_args3(t_genrsa_data *data, int *i, int ac
		, char **av)
{
	if (!ft_strcmp(av[*i], "-des"))
		data->crypt_method = "DES-CBC";
	else if (!ft_strcmp(av[*i], "-des2"))
		data->crypt_method = "DES-EDE-CBC";
	else if (!ft_strcmp(av[*i], "-des3"))
		data->crypt_method = "DES-EDE3-CBC";
	else if (!ft_strcmp(av[*i], "-aes128"))
		data->crypt_method = "AES-128-CBC";
	else if (!ft_strcmp(av[*i], "-aes192"))
		data->crypt_method = "AES-192-CBC";
	else if (!ft_strcmp(av[*i], "-aes256"))
		data->crypt_method = "AES-256-CBC";
	else if (!ft_strcmp(av[*i], "-camellia128"))
		data->crypt_method = "CAMELLIA-128-CBC";
	else if (!ft_strcmp(av[*i], "-camellia192"))
		data->crypt_method = "CAMELLIA-192-CBC";
	else if (!ft_strcmp(av[*i], "-camellia256"))
		data->crypt_method = "CAMELLIA-256-CBC";
	else
		return (0);
	return (1);
	(void)ac;
}

static int	cmd_genrsa_parse_args2(t_genrsa_data *data, int *i, int ac
		, char **av)
{
	int	lel;

	if (!ft_strcmp(av[*i], "-f4") || !ft_strcmp(av[*i], "-F4"))
		data->exp = 0x10001;
	else if (!ft_strcmp(av[*i], "-3"))
		data->exp = 3;
	else if (!ft_strcmp(av[*i], "-passout"))
	{
		if (*i + 1 < ac)
			data->passout = av[++(*i)];
		else
		{
			ft_putendl_fd("ft_ssl: password expected after -passout", 2);
			return (-1);
		}
	}
	else if ((lel = cmd_genrsa_parse_args3(data, i, ac, av)) <= 0)
		return (lel);
	return (1);
}

int			cmd_genrsa_parse_args(t_genrsa_data *data, int ac, char **av)
{
	int	lel;
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-out"))
		{
			if (!handle_out(data, ac, av, &i))
				return (0);
		}
		else if (ft_strisdigit(av[i]))
			data->key_len = ft_atol(av[i]);
		else if ((lel = cmd_genrsa_parse_args2(data, &i, ac, av)) <= 0)
		{
			if (lel != -1)
			{
				ft_putstr_fd("ft_ssl: invalid argument: ", 2);
				ft_putendl_fd(av[i], 2);
			}
			return (0);
		}
		++i;
	}
	return (1);
}
