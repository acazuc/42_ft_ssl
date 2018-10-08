/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:50:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:48:15 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "libft.h"

static int	init_free(t_cipher_ctx *ctx)
{
	free(ctx->mod1);
	free(ctx->mod2);
	free(ctx->buff);
	free(ctx->ctx);
	return (0);
}

int			cipher_init(t_cipher_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	ctx->buff_pos = 0;
	ctx->ended = 0;
	ctx->mod1 = NULL;
	ctx->mod2 = NULL;
	ctx->buff = NULL;
	ctx->ctx = NULL;
	if (!(ctx->mod1 = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->mod2 = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->buff = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->ctx = malloc(ctx->cipher->ctx_size)))
		return (init_free(ctx));
	if (!ctx->cipher->init(ctx->ctx, key, iv))
		return (init_free(ctx));
	return (1);
}

static int	do_update_part(t_cipher_ctx *ctx)
{
	ctx->cipher->mod->premod(ctx, ctx->buff);
	if (!ctx->cipher->update(ctx->ctx, ctx->buff, ctx->mode))
		return (0);
	ctx->cipher->mod->postmod(ctx, ctx->buff);
	return (1);
}

int			cipher_update(t_cipher_ctx *ctx, uint8_t *data, size_t len)
{
	size_t	tmp;

	while (len + ctx->buff_pos >= ctx->cipher->block_size + (ctx->mode ? 1 : 0))
	{
		tmp = ctx->cipher->block_size - ctx->buff_pos;
		ft_memcpy(ctx->buff + ctx->buff_pos, data, tmp);
		if (!do_update_part(ctx))
			return (0);
		if (!ctx->callback(ctx->userptr, ctx->buff, ctx->cipher->block_size))
			return (0);
		data += tmp;
		len -= tmp;
		ctx->buff_pos = 0;
	}
	ft_memcpy(ctx->buff + ctx->buff_pos, data, len);
	ctx->buff_pos += len;
	return (1);
}

int			cipher_final(t_cipher_ctx *ctx)
{
	int	ret;

	if (!ctx->mode && !ctx->cipher->mod->nopad)
	{
		ft_memset(ctx->buff + ctx->buff_pos, ctx->cipher->block_size
			- ctx->buff_pos, ctx->cipher->block_size - ctx->buff_pos);
		ctx->buff_pos = ctx->cipher->block_size;
	}
	ctx->ended = 1;
	ret = do_update_part(ctx);
	if (ctx->mode && !ctx->cipher->mod->nopad)
	{
		if (ctx->buff[ctx->buff_pos - 1] > ctx->cipher->block_size)
			ret = 0;
		ctx->buff_pos -= ctx->buff[ctx->buff_pos - 1];
	}
	if (ret && !ctx->callback(ctx->userptr, ctx->buff, ctx->buff_pos))
		ret = 0;
	free(ctx->buff);
	free(ctx->mod1);
	free(ctx->mod2);
	free(ctx->ctx);
	return (ret);
}
