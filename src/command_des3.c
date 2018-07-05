/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:15:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 16:05:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	init(t_des_data *data, t_des_args *args, int ac, char **av)
{
	data->fdout = 1;
	data->fdin = 0;
	data->cipher.mode = 0;
	args->password = NULL;
	args->salt = NULL;
	args->key = NULL;
	args->iv = NULL;
	args->av = av;
	args->ac = ac;
	args->i = 0;
	cipher_init(&data->cipher, 8);
}

static int	update(t_des_data *ctx, uint64_t *data, size_t len)
{
	*data = ft_swap_ulong(*data);
	if (ctx->cipher.mode)
	{
		if (!des_decrypt_update(&ctx->ctx[0], data, len))
			return (0);
		if (!des_encrypt_update(&ctx->ctx[1], data, len))
			return (0);
		if (!des_decrypt_update(&ctx->ctx[2], data, len))
			return (0);
	}
	else
	{
		if (!des_encrypt_update(&ctx->ctx[0], data, len))
			return (0);
		if (!des_decrypt_update(&ctx->ctx[1], data, len))
			return (0);
		if (!des_encrypt_update(&ctx->ctx[2], data, len))
			return (0);
	}
	*data = ft_swap_ulong(*data);
	return (1);
}

int		command_des3(int ac, char **av, t_des_data *data)
{
	t_des_args	args;

	data->cipher.update = (t_cipher_update)&update;
	data->cipher.callback = (t_cipher_cb)&cmd_des_callback;
	data->cipher.userptr = data;
	data->des3 = 1;
	init(data, &args, ac, av);
	if (!cmd_des_parse_args(data, &args) || !cmd_des_handle_key(data, &args)
			|| !cmd_des_handle_iv(data, &args) || !cmd_des_do_execute(data))
	{
		cipher_free(&data->cipher);
		return (EXIT_FAILURE);
	}
	cipher_free(&data->cipher);
	return (EXIT_SUCCESS);
}
