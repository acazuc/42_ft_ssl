/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:50:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 15:54:27 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_update_part(t_cipher_ctx *ctx)
{
	ctx->premod(ctx, ctx->buff);
	ctx->update(ctx->userptr, ctx->buff, ctx->buff_pos);
	ctx->postmod(ctx, ctx->buff);
	return (ctx->callback(ctx->userptr, ctx->buff, ctx->buff_pos));
}

static void	do_pad(t_cipher_ctx *ctx)
{
	if (ctx->mode || ctx->nopad)
		return ;
	ft_memset(ctx->buff + ctx->buff_pos, ctx->block_size - ctx->buff_pos
			, ctx->block_size - ctx->buff_pos);
	ctx->buff_pos = ctx->block_size;
}

int		cipher_update(t_cipher_ctx *ctx, uint8_t *data, size_t len)
{
	size_t	tmp;

	while (len + ctx->buff_pos >= ctx->block_size + (ctx->mode ? 1 : 0))
	{
		tmp = ctx->block_size - ctx->buff_pos;
		ft_memcpy(ctx->buff + ctx->buff_pos, data, tmp);
		ctx->buff_pos = ctx->block_size;
		if (!do_update_part(ctx))
			return (0);
		data += tmp;
		len -= tmp;
		ctx->buff_pos = 0;
	}
	ft_memcpy(ctx->buff + ctx->buff_pos, data, len);
	ctx->buff_pos += len;
	return (1);
}

int		cipher_final(t_cipher_ctx *ctx)
{
	do_pad(ctx);
	if (!ctx->buff_pos)
		return (1);
	ctx->ended = 1;
	return (do_update_part(ctx));
}
