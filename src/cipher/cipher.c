/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:50:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 18:22:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include "libft.h"

int		cipher_init(t_cipher_ctx *ctx, uint32_t block_size)
{
	ctx->block_size = block_size;
	ctx->buff_pos = 0;
	ctx->ended = 0;
	if (!(ctx->iv = malloc(block_size)))
		return (0);
	if (!(ctx->mod1 = malloc(block_size)))
	{
		free(ctx->iv);
		return (0);
	}
	if (!(ctx->mod2 = malloc(block_size)))
	{
		free(ctx->mod1);
		free(ctx->iv);
		return (0);
	}
	if (!(ctx->buff = malloc(block_size)))
	{
		free(ctx->mod1);
		free(ctx->mod2);
		free(ctx->iv);
		return (0);
	}
	return (1);
}

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
	int	ret;

	do_pad(ctx);
	ctx->ended = 1;
	ret = do_update_part(ctx);
	free(ctx->buff);
	free(ctx->mod1);
	free(ctx->mod2);
	free(ctx->iv);
	return (ret);
}
