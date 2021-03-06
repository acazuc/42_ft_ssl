/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:54:15 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:39:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/hash.h"
#include "pbkdf2.h"
#include "libft.h"
#include "hmac.h"

static int	loop_part(t_pbkdf2_ctx *ctx, t_hmac_ctx *hmac_ctx
		, uint8_t *hash_tmp, uint8_t *sum)
{
	uint32_t	j;
	uint8_t		*hash_tmp2;

	j = 1;
	while (j < ctx->iterations)
	{
		hmac_ctx->msg = hash_tmp;
		hmac_ctx->msg_len = ctx->h.hash->digest_len;
		hash_tmp2 = hmac(hmac_ctx);
		free(hash_tmp);
		if (!hash_tmp2)
			return (0);
		hash_tmp = hash_tmp2;
		ft_memxor(sum, sum, hash_tmp, ctx->h.hash->digest_len);
		++j;
	}
	free(hash_tmp);
	return (1);
}

static int	loop(t_pbkdf2_ctx *ctx, int i_swap, uint8_t *tmp
		, uint8_t *sum)
{
	t_hmac_ctx	hmac_ctx;
	uint8_t		*hash_tmp;

	hmac_ctx.h = ctx->h;
	ft_memcpy(tmp, ctx->salt, ctx->salt_len);
	ft_memcpy(tmp + ctx->salt_len, &i_swap, 4);
	hmac_ctx.msg = tmp;
	hmac_ctx.msg_len = ctx->salt_len + 4;
	hmac_ctx.key = ctx->password;
	hmac_ctx.key_len = ctx->password_len;
	if (!(hash_tmp = hmac(&hmac_ctx)))
		return (0);
	ft_memcpy(sum, hash_tmp, ctx->h.hash->digest_len);
	if (!loop_part(ctx, &hmac_ctx, hash_tmp, sum))
		return (0);
	return (1);
}

static int	pbkdf2_init(t_pbkdf2_ctx *ctx, uint8_t **sum, uint8_t **ret
		, uint32_t *blocks)
{
	if (!(*sum = malloc(ctx->h.hash->digest_len)))
		return (0);
	*blocks = ctx->out_len / ctx->h.hash->digest_len
		+ (ctx->out_len % ctx->h.hash->digest_len > 0 ? 1 : 0);
	if (!(*ret = malloc(*blocks * ctx->h.hash->digest_len)))
	{
		free(*sum);
		return (0);
	}
	return (1);
}

static int	pbkdf2_free(uint8_t *sum, uint8_t *tmp, uint8_t *ret)
{
	free(sum);
	free(tmp);
	free(ret);
	return (0);
}

int			pbkdf2(t_pbkdf2_ctx *ctx)
{
	uint32_t	blocks;
	uint32_t	i;
	uint8_t		*tmp;
	uint8_t		*sum;
	uint8_t		*ret;

	if (!pbkdf2_init(ctx, &sum, &ret, &blocks))
		return (0);
	if (!(tmp = malloc(ctx->salt_len + 4)))
		return (0);
	i = -1;
	while (++i < blocks)
	{
		if (!loop(ctx, ft_swap_uint(i + 1), tmp, sum))
			return (pbkdf2_free(sum, tmp, ret));
		ft_memcpy(ret + i * ctx->h.hash->digest_len, sum
				, ctx->h.hash->digest_len);
	}
	ft_memcpy(ctx->out, ret, ctx->out_len);
	pbkdf2_free(sum, tmp, ret);
	return (1);
}
