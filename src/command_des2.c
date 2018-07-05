/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:10:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 12:29:57 by acazuc           ###   ########.fr       */
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

int	command_des2(int ac, char **av, t_des_data *data)
{
	t_des_args	args;

	init(data, &args, ac, av);
	if (!cmd_des_parse_args(data, &args))
		return (EXIT_FAILURE);
	if (data->mode)
		data->ctx[0].callback = (t_des_callback)des_encrypt_update;
	else
		data->ctx[0].callback = (t_des_callback)des_decrypt_update;
	data->ctx[0].userptr = &data->ctx[1];
	if (data->mode)
		data->ctx[1].callback = (t_des_callback)des_decrypt_update;
	else
		data->ctx[1].callback = (t_des_callback)des_encrypt_update;
	data->ctx[1].userptr = &data->ctx[2];
	data->ctx[2].callback = NULL;
	data->des3 = 1;
	if (!cmd_des_handle_key(data, &args))
		return (EXIT_FAILURE);
	data->keys[2] = data->keys[0];
	if (!cmd_des_handle_iv(data, &args))
		return (EXIT_FAILURE);
	if (!cmd_des_do_execute(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
