/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:54:15 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:58:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	loop(t_pbkdf2_ctx *ctx, int i_swap, uint8_t *tmp
		, uint8_t *sum)
{
	t_hmac_ctx	hmac_ctx;
	uint32_t	j;
	uint8_t		*hash_tmp;
	uint8_t		*hash_tmp2;

	hmac_ctx.h = ctx->h;
	ft_memcpy(tmp, ctx->salt, ctx->salt_len);
	ft_memcpy(tmp + ctx->salt_len, &i_swap, 4);
	hmac_ctx.key = tmp;
	hmac_ctx.key_len = ctx->salt_len + 4;
	hmac_ctx.msg = ctx->password;
	hmac_ctx.msg_len = ctx->password_len;
	if (!(hash_tmp = hmac(&hmac_ctx)))
	{
		free(sum);
		return (0);
	}
	ft_memcpy(sum, hash_tmp, ctx->h.h->digest_len);
	j = 0;
	while (j < ctx->iterations)
	{
		hmac_ctx.key = hash_tmp;
		hmac_ctx.key_len = ctx->h.h->digest_len;
		if (!(hash_tmp2 = hmac(&hmac_ctx)))
		{
			free(sum);
			free(hash_tmp);
			return (0);
		}
		free(hash_tmp);
		hash_tmp = hash_tmp2;
		ft_memxor(sum, sum, hash_tmp, ctx->h.h->digest_len);
		++j;
	}
	return (1);
}

char		*pbkdf2(t_pbkdf2_ctx *ctx)
{
	uint32_t	blocks;
	uint32_t	i;
	uint8_t		*tmp;
	uint8_t		*sum;
	uint8_t		*ret;

	if (!(tmp = malloc(ctx->salt_len + 4)))
		return (NULL);
	if (!(sum = malloc(ctx->h.h->digest_len)))
	{
		free(tmp);
		return (NULL);
	}
	blocks = ctx->out_len / ctx->h.h->digest_len
		+ (ctx->out_len % ctx->h.h->digest_len > 0 ? 1 : 0);
	if (!(ret = malloc(blocks * ctx->h.h->digest_len)))
	{
		free(tmp);
		free(sum);
		return (NULL);
	}
	i = -1;
	while (++i <= blocks)
	{
		if (!loop(ctx, ft_swap_uint(i + 1), tmp, sum))
		{
			free(sum);
			free(tmp);
			free(ret);
			return (NULL);
		}
		ft_memcpy(ret + i * ctx->h.h->digest_len, sum, ctx->h.h->digest_len);
	}
	ft_memcpy(ctx->out, ret, ctx->out_len);
	free(ret);
	return (NULL);
}
