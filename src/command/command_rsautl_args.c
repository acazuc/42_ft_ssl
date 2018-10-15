/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 11:35:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 12:23:16 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	cmd_rsautl_args2(t_rsautl_data *data, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-hexdump"))
		data->hexdump = 1;
	else if (!ft_strcmp(av[*i], "-passin"))
	{
		if (!cmd_rsautl_handle_passin(data, ac, av, i))
			return (0);
	}
	else if (!ft_strcmp(av[*i], "-inkey"))
	{
		if (!cmd_rsautl_handle_inkey(data, ac, av, i))
			return (0);
	}
	else if (!ft_strcmp(av[*i], "-sign"))
		data->mode = RSAUTL_MODE_SIGN;
	else if (!ft_strcmp(av[*i], "-verify"))
		data->mode = RSAUTL_MODE_VERIFY;
	else
	{
		ft_putstr_fd("ft_ssl: unexpected argument: ", 2);
		ft_putendl_fd(av[*i], 2);
		return (0);
	}
	return (1);
}

int			cmd_rsautl_args(t_rsautl_data *data, int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-in"))
		{
			if (!cmd_rsautl_handle_in(data, ac, av, &i))
				return (0);
		}
		else if (!ft_strcmp(av[i], "-out"))
		{
			if (!cmd_rsautl_handle_out(data, ac, av, &i))
				return (0);
		}
		else if (!ft_strcmp(av[i], "-pubin"))
			data->pubin = 1;
		else if (!ft_strcmp(av[i], "-encrypt"))
			data->mode = RSAUTL_MODE_ENCRYPT;
		else if (!ft_strcmp(av[i], "-decrypt"))
			data->mode = RSAUTL_MODE_DECRYPT;
		else if (!cmd_rsautl_args2(data, ac, av, &i))
			return (0);
	}
	return (1);
}
