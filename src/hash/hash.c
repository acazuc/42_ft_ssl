/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 19:45:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 19:58:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/hash.h"
#include <stdlib.h>

int	hash_init(t_hash_ctx *ctx, t_hash *hash)
{
	ctx->hash = hash;
	if (!(ctx->ctx = malloc(hash->ctx_len)))
		return (0);
	if (!ctx->hash->init(ctx->ctx))
	{
		free(ctx->ctx);
		return (0);
	}
	return (1);
}

int	hash_update(t_hash_ctx *ctx, uint8_t *data, size_t len)
{
	return (ctx->hash->update(ctx->ctx, data, len));
}

int	hash_final(t_hash_ctx *ctx, uint8_t *md)
{
	int	ret;

	ret = ctx->hash->final(md, ctx->ctx);
	free(ctx->ctx);
	return (ret);
}
