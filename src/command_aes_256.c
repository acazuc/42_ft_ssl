/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_256.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:39:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 19:20:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	update(t_aes_data *ctx, uint8_t *data, size_t len)
{
	if (ctx->cipher.mode)
	{
		if (!aes_decrypt_update(&ctx->ctx, data, len))
			return (0);
	}
	else
	{
		if (!aes_encrypt_update(&ctx->ctx, data, len))
			return (0);
	}
	return (1);
}

int		command_aes_256(int ac, char **av, t_aes_data *data)
{
	t_aes_args	args;

	data->cipher.update = (t_cipher_update)&update;
	data->cipher.callback = (t_cipher_cb)&cmd_aes_callback;
	data->cipher.userptr = data;
	data->key_size = 32;
	if (!cmd_aes_init(data, &args, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_aes_parse_args(data, &args) || !cmd_aes_handle_key(data, &args)
			|| !cmd_aes_handle_iv(data, &args) || !cmd_aes_do_execute(data))
	{
		cmd_aes_free(data);
		return (EXIT_FAILURE);
	}
	cmd_aes_free(data);
	return (EXIT_SUCCESS);
}
