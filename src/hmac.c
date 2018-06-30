/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:57:54 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 15:02:49 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t	*hmac_check_key_len1(t_hmac_ctx *ctx
		, uint8_t *key, uint32_t key_len
		, uint32_t *tmp_len)
{
	uint8_t	*tmp;

	if (key_len > ctx->h.h->block_len)
	{
		if (!ctx->h.h->init(ctx->h.ctx))
			return (NULL);
		if (!ctx->h.h->update(ctx->h.ctx, key, key_len))
			return (NULL);
		if (!(tmp = malloc(ctx->h.h->digest_len)))
			return (NULL);
		if (!ctx->h.h->final(tmp, ctx->h.ctx))
		{
			free(tmp);
			return (NULL);
		}
		*tmp_len = ctx->h.h->digest_len;
		return (tmp);
	}
	if (!(tmp = malloc(key_len)))
		return (NULL);
	*tmp_len = key_len;
	ft_memcpy(tmp, key, key_len);
	return (tmp);
}

static int	hmac_check_key_len2(t_hmac_ctx *ctx
		, uint8_t **tmp, uint32_t *tmp_len)
{
	uint32_t	i;
	uint8_t		*tmp2;

	if (*tmp_len >= ctx->h.h->block_len)
		return (1);
	if (!(tmp2 = malloc(ctx->h.h->block_len)))
		return (0);
	ft_memcpy(tmp2, *tmp, *tmp_len);
	i = *tmp_len;
	while (i < ctx->h.h->block_len)
	{
		tmp2[i] = 0;
		++i;
	}
	free(*tmp);
	*tmp = tmp2;
	*tmp_len = ctx->h.h->block_len;
	return (1);
}

static int	create_pads(t_hmac_ctx *ctx, uint8_t **pads, uint8_t *key)
{
	int	i;

	if (!(pads[0] = malloc(ctx->h.h->block_len)))
		return (0);
	if (!(pads[1] = malloc(ctx->h.h->block_len)))
	{
		free(pads[0]);
		return (0);
	}
	i = 0;
	while (i < ctx->h.h->block_len)
	{
		pads[0][i] = key[i] ^ 0x5c;
		pads[1][i] = key[i] ^ 0x36;
		++i;
	}
	return (1);
}

static uint8_t	*do_final(t_hmac_ctx *ctx, uint8_t **pads, uint8_t **tmp)
{
	uint8_t	*tmp2;

	if (!ctx->h.h->init(ctx->h.ctx))
		return (NULL);
	if (!ctx->h.h->update(ctx->h.ctx, pads[1], ctx->h.h->block_len))
		return (NULL);
	if (!ctx->h.h->update(ctx->h.ctx, ctx->msg, ctx->msg_len))
		return (NULL);
	if (!(*tmp = malloc(ctx->h.h->digest_len)))
		return (NULL);
	if (!ctx->h.h->final(*tmp, ctx->h.ctx))
		return (NULL);
	if (!ctx->h.h->init(ctx->h.ctx))
		return (NULL);
	if (!(ctx->h.h->update(ctx->h.ctx, pads[0], ctx->h.h->block_len)))
		return (NULL);
	if (!(ctx->h.h->update(ctx->h.ctx, *tmp, ctx->h.h->digest_len)))
		return (NULL);
	if (!ctx->h.h->final(*tmp, ctx->h.ctx))
		return (NULL);
	tmp2 = *tmp;
	*tmp = NULL;
	return (tmp2);
}

uint8_t		*hmac(t_hmac_ctx *ctx)
{
	uint32_t	tmp_len;
	uint8_t		*pads[2];
	uint8_t		*result;
	uint8_t		*tmp;

	if (!(tmp = hmac_check_key_len1(ctx, ctx->key, ctx->key_len
					, &tmp_len)))
		return (NULL);
	if (!hmac_check_key_len2(ctx, &tmp, &tmp_len))
	{
		free(tmp);
		return (NULL);
	}
	if (!create_pads(ctx, pads, tmp))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	tmp = NULL;
	result = do_final(ctx, pads, &tmp);
	free(tmp);
	free(pads[0]);
	free(pads[1]);
	return (result);
}
