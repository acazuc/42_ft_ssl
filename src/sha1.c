/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 22:21:08 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:22:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha1.h"

t_hash		g_hash_sha1 = {(t_hash_init*)sha1_init
		, (t_hash_update*)sha1_update, (t_hash_final*)sha1_final
		, 20, 64, "SHA1"};

static uint32_t		g_sha1_k[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC
	, 0xCA62C1D6};

static void	sha1_loop(int i, uint32_t *tmp, uint32_t *w)
{
	uint32_t tmp1;
	uint32_t f;
	uint32_t k;

	k = g_sha1_k[i / 20];
	if (i <= 19)
		f = (tmp[1] & tmp[2]) | ((~tmp[1]) & tmp[3]);
	else if (i <= 39)
		f = tmp[1] ^ tmp[2] ^ tmp[3];
	else if (i <= 59)
		f = (tmp[1] & tmp[2]) | (tmp[1] & tmp[3]) | (tmp[2] & tmp[3]);
	else
		f = tmp[1] ^ tmp[2] ^ tmp[3];
	tmp1 = rotate_left32(tmp[0], 5) + f + tmp[4] + k + w[i];
	tmp[4] = tmp[3];
	tmp[3] = tmp[2];
	tmp[2] = rotate_left32(tmp[1], 30);
	tmp[1] = tmp[0];
	tmp[0] = tmp1;
}

static void	sha1_chunk(t_sha1_ctx *ctx)
{
	uint32_t	tmp[5];
	uint32_t	w[80];
	int		i;

	i = -1;
	while (++i < 16)
		w[i] = ft_swap_uint(ctx->data[i]);
	while (i < 80)
	{
		w[i] = rotate_left32(w[i - 3] ^ w[i - 8] ^ w[i - 14]
				^ w[i - 16], 1);
		++i;
	}
	i = -1;
	while (++i < 5)
		tmp[i] = ctx->h[i];
	i = -1;
	while (++i < 80)
		sha1_loop(i, tmp, w);
	i = -1;
	while (++i < 5)
		ctx->h[i] += tmp[i];
}

int		sha1_init(t_sha1_ctx *ctx)
{
	ctx->total_len = 0;
	ctx->data_len = 0;
	ctx->h[0] = 0x67452301;
	ctx->h[1] = 0xEFCDAB89;
	ctx->h[2] = 0x98BADCFE;
	ctx->h[3] = 0x10325476;
	ctx->h[4] = 0xC3D2E1F0;
	return (1);
}

int		sha1_update(t_sha1_ctx *ctx, const uint8_t *data, size_t len)
{
	while (1)
	{
		if (ctx->data_len + len < 64)
		{
			ft_memcpy((char*)ctx->data + ctx->data_len, data, len);
			ctx->data_len += len;
			ctx->total_len += len;
			return (1);
		}
		ft_memcpy((char*)ctx->data + ctx->data_len, data, 64 - ctx->data_len);
		len -= 64 - ctx->data_len;
		data += 64 - ctx->data_len;
		ctx->total_len += 64 - ctx->data_len;
		ctx->data_len = 0;
		sha1_chunk(ctx);
	}
	return (1);
}

int		sha1_final(uint8_t *md, t_sha1_ctx *ctx)
{
	int	i;

	((char*)ctx->data)[ctx->data_len] = 0x80;
	ctx->data_len++;
	if (ctx->data_len > 56)
	{
		while (ctx->data_len < 64)
			((char*)ctx->data)[ctx->data_len++] = 0;
		sha1_update(ctx, NULL, 0);
	}
	while (ctx->data_len < 56)
		((char*)ctx->data)[ctx->data_len++] = 0;
	ctx->total_len = ft_swap_ulong(ctx->total_len * 8);
	ft_memcpy(ctx->data + 14, &ctx->total_len, 8);
	ctx->data_len = 64;
	sha1_update(ctx, NULL, 0);
	i = -1;
	while (++i < 5)
	{
		md[i * 4 + 0] = ctx->h[i] >> 24;
		md[i * 4 + 1] = ctx->h[i] >> 16;
		md[i * 4 + 2] = ctx->h[i] >> 8;
		md[i * 4 + 3] = ctx->h[i] >> 0;
	}
	return (1);
}
