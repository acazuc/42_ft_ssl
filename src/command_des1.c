/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:25:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 12:29:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	init(t_des_data *data, t_des_args *args, int ac, char **av)
{
	data->fdout = 1;
	data->fdin = 0;
	data->mode = 0;
	args->password = NULL;
	args->salt = NULL;
	args->key = NULL;
	args->iv = NULL;
	args->av = av;
	args->ac = ac;
	args->i = 0;
}

int		command_des(int ac, char **av, t_des_data *data)
{
	t_des_args	args;

	data->ctx[0].callback = NULL;
	data->des3 = 0;
	init(data, &args, ac, av);
	if (!cmd_des_parse_args(data, &args))
		return (EXIT_FAILURE);
	if (!cmd_des_handle_key(data, &args))
		return (EXIT_FAILURE);
	if (!cmd_des_handle_iv(data, &args))
		return (EXIT_FAILURE);
	if (!cmd_des_do_execute(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
