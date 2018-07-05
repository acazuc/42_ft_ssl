/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 21:27:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 15:51:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_init(t_des_ctx *ctx, uint64_t key, int mode)
{
	key = ft_swap_ulong(key);
	if (mode)
		return (des_decrypt_init(ctx, key));
	return (des_encrypt_init(ctx, key));
}

static	int	do_update(t_des_data *data)
{
	uint8_t	buff[4096];
	int	ret;

	while ((ret = read(data->fdin, buff, 4096)) > 0)
	{
		if (!cipher_update(&data->cipher, buff, ret))
			return (0);
	}
	if (ret == -1)
		return (0);
	if (!cipher_final(&data->cipher))
		return (0);
	return (1);
}

static int	do_final(t_des_ctx *ctx, int mode)
{
	if (mode)
		return (des_decrypt_final(ctx));
	return (des_encrypt_final(ctx));
}

int		cmd_des_do_execute(t_des_data *data)
{
	uint64_t	tmp;

	ft_memcpy(data->cipher.mod1, data->cipher.iv, data->cipher.block_size);
	if (data->des3 && data->cipher.mode)
	{
		tmp = data->keys[0];
		data->keys[0] = data->keys[2];
		data->keys[2] = tmp;
	}
	if (!do_init(&data->ctx[0], data->keys[0], data->cipher.mode)
			|| (data->des3 && !do_init(&data->ctx[1], data->keys[1], !data->cipher.mode))
			|| (data->des3 && !do_init(&data->ctx[2], data->keys[2], data->cipher.mode)))
	{
		ft_putendl_fd("ft_ssl: error while initializing des", 2);
		return (0);
	}
	if (!do_update(data))
		return (0);
	if (!do_final(&data->ctx[0], data->cipher.mode)
			|| (data->des3 && !do_final(&data->ctx[1], !data->cipher.mode))
			|| (data->des3 && !do_final(&data->ctx[2], data->cipher.mode)))
	{
		ft_putendl_fd("ft_ssl: error while finalizing des", 2);
		return (0);
	}
	return (1);
}
