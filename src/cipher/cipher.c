/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:50:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:35:06 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "libft.h"

static int	init_free(t_cipher_ctx *ctx)
{
	free(ctx->mod1);
	free(ctx->mod2);
	free(ctx->iv);
	free(ctx->buff);
	free(ctx->ctx);
	return (0);
}

int		cipher_init(t_cipher_ctx *ctx, t_cipher *cipher, uint8_t *key)
{
	ctx->cipher = cipher;
	ctx->buff_pos = 0;
	ctx->ended = 0;
	ctx->iv = NULL;
	ctx->mod1 = NULL;
	ctx->mod2 = NULL;
	ctx->buff = NULL;
	ctx->ctx = NULL;
	if (!(ctx->iv = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->mod1 = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->mod2 = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->buff = malloc(ctx->cipher->block_size)))
		return (init_free(ctx));
	if (!(ctx->ctx = malloc(ctx->cipher->ctx_size)))
		return (init_free(ctx));
	if (!cipher->init(ctx->ctx, key))
		return (init_free(ctx));
	return (1);
}

static int	do_update_part(t_cipher_ctx *ctx)
{
	ctx->mod->premod(ctx, ctx->buff);
	if (!ctx->cipher->update(ctx->ctx, ctx->buff, ctx->mode))
		return (0);
	ctx->mod->postmod(ctx, ctx->buff);
	return (ctx->callback(ctx->userptr, ctx->buff, ctx->buff_pos));
}

int		cipher_update(t_cipher_ctx *ctx, uint8_t *data, size_t len)
{
	size_t	tmp;

	while (len + ctx->buff_pos >= ctx->cipher->block_size + (ctx->mode ? 1 : 0))
	{
		tmp = ctx->cipher->block_size - ctx->buff_pos;
		ft_memcpy(ctx->buff + ctx->buff_pos, data, tmp);
		ctx->buff_pos = ctx->cipher->block_size;
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

	if (!ctx->mode && !ctx->mod->nopad)
	{
		ft_memset(ctx->buff + ctx->buff_pos, ctx->cipher->block_size
			- ctx->buff_pos, ctx->cipher->block_size - ctx->buff_pos);
		ctx->buff_pos = ctx->cipher->block_size;
	}
	ctx->ended = 1;
	ret = do_update_part(ctx);
	free(ctx->buff);
	free(ctx->mod1);
	free(ctx->mod2);
	free(ctx->iv);
	free(ctx->ctx);
	return (ret);
}
