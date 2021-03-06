/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cipher_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 17:22:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 18:46:57 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_update(t_cipher_data *data)
{
	uint8_t	buff[1024 * 16];
	int		ret;

	while ((ret = read(data->fdin, buff, 1024 * 16)) > 0)
	{
		if (data->base64 && data->cipher.mode)
		{
			if (!b64d_update(&data->b64d_ctx, buff, ret))
			{
				ft_putendl_fd("ft_ssl: cipher error", 2);
				return (0);
			}
		}
		else if (!cipher_update(&data->cipher, buff, ret))
		{
			ft_putendl_fd("ft_ssl: cipher error", 2);
			return (0);
		}
	}
	if (ret == -1)
	{
		ft_putendl_fd("ft_ssl: error while reading file", 2);
		return (0);
	}
	return (1);
}

static int	handle_b64(t_cipher_data *data)
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

int			cmd_cipher_do_execute(t_cipher_data *data)
{
	ft_memcpy(data->cipher.mod1, data->iv, data->cipher.cipher->block_size);
	if (!handle_b64(data))
		return (0);
	if (!do_update(data))
		return (0);
	if (!cipher_final(&data->cipher))
	{
		ft_putendl_fd("ft_ssl: invalid cipher final", 2);
		return (0);
	}
	return (1);
}
