/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 17:22:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:04:03 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_init(t_aes_ctx *ctx, uint8_t *key, int key_size, int mode)
{
	if (mode)
	{
		if (!aes_decrypt_init(ctx, key, key_size))
		{
			ft_putendl_fd("ft_ssl: aes initialize failed", 2);
			return (0);
		}
		return (1);
	}
	if (!aes_encrypt_init(ctx, key, key_size))
	{
		ft_putendl_fd("ft_ssl: aes initialize failed", 2);
		return (0);
	}
	return (1);
}

static	int	do_update(t_aes_data *data)
{
	uint8_t	buff[4096];
	int	ret;

	while ((ret = read(data->fdin, buff, 4096)) > 0)
	{
		if (data->base64 && data->cipher.mode)
		{
			if (!b64d_update(&data->b64d_ctx, buff, ret))
				return (0);
			continue;
		}
		if (!cipher_update(&data->cipher, buff, ret))
			return (0);
	}
	if (ret == -1)
		return (0);
	if (!cipher_final(&data->cipher))
		return (0);
	return (1);
}

static int	do_final(t_aes_ctx *ctx, int mode)
{
	if (mode)
	{
		if (!aes_decrypt_final(ctx))
		{
			ft_putendl_fd("ft_ssl: aes finalize failed", 2);
			return (0);
		}
		return (1);
	}
	if (!aes_encrypt_final(ctx))
	{
		ft_putendl_fd("ft_ssl: aes finalize failed", 2);
		return (0);
	}
	return (1);
}

static int	handle_b64(t_aes_data *data)
{
	if (!data->base64)
		return (1);
	if (data->cipher.mode)
	{
		if (!b64d_init(&data->b64d_ctx))
		{
			ft_putendl_fd("ft_ssl: base64 decrypt init failed", 2);
			return (0);
		}
		data->b64d_ctx.callback = (t_b64_callback)cipher_update;
		data->b64d_ctx.userptr = &data->cipher;
	}
	else
	{
		if (!base64_write_init(&data->b64e_ctx))
		{
			ft_putendl_fd("ft_ssl: base64 encrypt init failed", 2);
			return (0);
		}
	}
	return (1);
}

int		cmd_aes_do_execute(t_aes_data *data)
{
	ft_memcpy(data->cipher.mod1, data->cipher.iv, data->cipher.cipher->block_size);
	if (!handle_b64(data))
		return (0);
	if (!do_init(&data->ctx, data->key, data->key_size, data->cipher.mode))
		return (0);
	if (!do_update(data))
		return (0);
	if (!do_final(&data->ctx, data->cipher.mode))
		return (0);
	return (1);
}
