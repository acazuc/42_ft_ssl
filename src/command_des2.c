/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:10:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 19:46:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	update(t_des_data *ctx, uint8_t *data, size_t len)
{
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
	return (1);
}

int		command_des2(int ac, char **av, t_des_data *data)
{
	t_des_args	args;

	data->cipher.update = (t_cipher_update)&update;
	data->cipher.callback = (t_cipher_cb)&cmd_des_callback;
	data->cipher.userptr = data;
	data->des3 = 1;
	if (!cmd_des_init(data, &args, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_des_parse_args(data, &args) || !cmd_des_handle_key(data, &args))
	{
		cmd_des_free(data);
		return (EXIT_FAILURE);
	}
	data->keys[2] = data->keys[0];
	if (!cmd_des_handle_iv(data, &args) || !cmd_des_do_execute(data))
	{
		cmd_des_free(data);
		return (EXIT_FAILURE);
	}
	cmd_des_free(data);
	return (EXIT_SUCCESS);
}
