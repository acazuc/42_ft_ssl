/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:25:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 15:38:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	callback(void *userptr, uint8_t *data, size_t len)
{
	t_des_data	*datas;
	int osef;

	datas = (t_des_data*)userptr;
	osef = write(datas->fdout, data, len);
	(void)osef;
	return (1);
}

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

	data->ctx1.callback = callback;
	data->ctx1.userptr = data;
	data->des3 = 0;
	init(data, &args, ac, av);
	if (!cmd_des_parse_args(data, &args))
		return (EXIT_FAILURE);
	if (!cmd_des_handle_key(data, &args))
		return (EXIT_FAILURE);
	if (!cmd_des_handle_iv(&data->ctx1, args.iv))
		return (EXIT_FAILURE);
	if (!cmd_des_do_execute(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
