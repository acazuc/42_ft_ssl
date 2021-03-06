/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cipher_callback.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 17:18:16 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 14:24:34 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	do_update_buff(t_cipher_data *ctx, uint8_t *data, size_t len)
{
	int	osef;

	while (len + ctx->buff_pos >= 1024 * 16)
	{
		ft_memcpy(ctx->buff + ctx->buff_pos, data, 1024 * 16 - ctx->buff_pos);
		osef = write(ctx->fdout, ctx->buff, 1024 * 16);
		len -= 1024 * 16 - ctx->buff_pos;
		data += 1024 * 16 - ctx->buff_pos;
		ctx->buff_pos = 0;
	}
	ft_memcpy(ctx->buff + ctx->buff_pos, data, len);
	ctx->buff_pos += len;
	(void)osef;
}

static int	do_update(t_cipher_data *ctx, uint8_t *data, size_t len)
{
	if (!ctx->cipher.mode && ctx->base64)
	{
		ctx->b64e_ctx.fdout = ctx->fdout;
		if (!base64_write_update(&ctx->b64e_ctx, data, len))
		{
			ft_putendl_fd("ft_ssl: base64 encode failed", 2);
			return (0);
		}
		return (1);
	}
	do_update_buff(ctx, data, len);
	return (1);
}

int			cmd_cipher_callback(t_cipher_data *ctx, uint8_t *data, size_t len)
{
	if (!do_update(ctx, data, len))
		return (0);
	if (!ctx->cipher.mode && ctx->cipher.ended)
	{
		if (ctx->base64 && !base64_write_final(&ctx->b64e_ctx))
		{
			ft_putendl_fd("ft_ssl: base64 encode failed", 2);
			return (0);
		}
	}
	if (ctx->cipher.ended && ctx->buff_pos)
		len = write(ctx->fdout, ctx->buff, ctx->buff_pos);
	return (1);
}
