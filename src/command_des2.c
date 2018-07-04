/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:10:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 16:50:08 by acazuc           ###   ########.fr       */
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

int	command_des2(int ac, char **av, t_des_data *data)
{
	t_des_args	args;

	init(data, &args, ac, av);
	if (!cmd_des_parse_args(data, &args))
		return (EXIT_FAILURE);
	if (data->mode)
		data->ctx1.callback = (t_des_callback)des_encrypt_update;
	else
		data->ctx1.callback = (t_des_callback)des_decrypt_update;
	data->ctx1.userptr = &data->ctx2;
	if (data->mode)
		data->ctx2.callback = (t_des_callback)des_decrypt_update;
	else
		data->ctx2.callback = (t_des_callback)des_encrypt_update;
	data->ctx2.userptr = &data->ctx3;
	data->ctx3.callback = callback;
	data->ctx3.userptr = data;
	data->des3 = 1;
	data->ctx2.nopad = 1;
	data->ctx3.nopad = 1;
	if (data->mode)
	{
		data->ctx3.nopad = data->ctx1.nopad;
		data->ctx1.nopad = 1;
	}
	if (!cmd_des_handle_key(data, &args))
		return (EXIT_FAILURE);
	data->key3 = data->key1;
	if (!cmd_des_handle_iv(&data->ctx1, args.iv))
		return (EXIT_FAILURE);
	data->ctx2.iv = data->ctx1.iv;
	data->ctx3.iv = data->ctx1.iv;
	if (!cmd_des_do_execute(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
