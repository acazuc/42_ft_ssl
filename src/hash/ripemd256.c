/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripemd256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:01:49 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 12:24:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/ripemd256.h"
#include "ft_ssl.h"

t_hash		g_hash_ripemd256 = {"RIPEMD256",
	(t_hash_init)ripemd256_init,
	(t_hash_update)ripemd256_update,
	(t_hash_final)ripemd256_final,
	32, 64, sizeof(t_ripemd256_ctx)};

static uint8_t	g_ripemd256_g[128] = {
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
	0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	0x7, 0x4, 0xd, 0x1, 0xa, 0x6, 0xf, 0x3,
	0xc, 0x0, 0x9, 0x5, 0x2, 0xe, 0xb, 0x8,
	0x3, 0xa, 0xe, 0x4, 0x9, 0xf, 0x8, 0x1,
	0x2, 0x7, 0x0, 0x6, 0xd, 0xb, 0x5, 0xc,
	0x1, 0x9, 0xb, 0xa, 0x0, 0x8, 0xc, 0x4,
	0xd, 0x3, 0x7, 0xf, 0xe, 0x5, 0x6, 0x2,
	0x5, 0xe, 0x7, 0x0, 0x9, 0x2, 0xb, 0x4,
	0xd, 0x6, 0xf, 0x8, 0x1, 0xa, 0x3, 0xc,
	0x6, 0xb, 0x3, 0x7, 0x0, 0xd, 0x5, 0xa,
	0xe, 0xf, 0x8, 0xc, 0x4, 0x9, 0x1, 0x2,
	0xf, 0x5, 0x1, 0x3, 0x7, 0xe, 0x6, 0x9,
	0xb, 0x8, 0xc, 0x2, 0xa, 0x0, 0x4, 0xd,
	0x8, 0x6, 0x4, 0x1, 0x3, 0xb, 0xf, 0x0,
	0x5, 0xc, 0x2, 0xd, 0x9, 0x7, 0xa, 0xe};

static uint8_t	g_ripemd256_s[128] = {
	0xb, 0xe, 0xf, 0xc, 0x5, 0x8, 0x7, 0x9,
	0xb, 0xd, 0xe, 0xf, 0x6, 0x7, 0x9, 0x8,
	0x7, 0x6, 0x8, 0xd, 0xb, 0x9, 0x7, 0xf,
	0x7, 0xc, 0xf, 0x9, 0xb, 0x7, 0xd, 0xc,
	0xb, 0xd, 0x6, 0x7, 0xe, 0x9, 0xd, 0xf,
	0xe, 0x8, 0xd, 0x6, 0x5, 0xc, 0x7, 0x5,
	0xb, 0xc, 0xe, 0xf, 0xe, 0xf, 0x9, 0x8,
	0x9, 0xe, 0x5, 0x6, 0x8, 0x6, 0x5, 0xc,
	0x8, 0x9, 0x9, 0xb, 0xd, 0xf, 0xf, 0x5,
	0x7, 0x7, 0x8, 0xb, 0xe, 0xe, 0xc, 0x6,
	0x9, 0xd, 0xf, 0x7, 0xc, 0x8, 0x9, 0xb,
	0x7, 0x7, 0xc, 0x7, 0x6, 0xf, 0xd, 0xb,
	0x9, 0x7, 0xf, 0xb, 0x8, 0x6, 0x6, 0xe,
	0xc, 0xd, 0x5, 0xe, 0xd, 0xd, 0x7, 0x5,
	0xf, 0x5, 0x8, 0xb, 0xe, 0xe, 0x6, 0xe,
	0x6, 0x9, 0xc, 0x9, 0xc, 0x5, 0xf, 0x8};

static uint32_t	g_ripemd256_k[8] = {
	0x00000000, 0x5a827999, 0x6ed9eba1, 0x8f1bbcdc,
	0x50a28be6, 0x5c4dd124, 0x6d703ef3, 0x00000000};

static void	ripemd256_loop(t_ripemd256_ctx *ctx, int i, uint32_t *tmp, int ofs)
{
	uint32_t	f;

	if ((ofs ? 63 - i : i) <= 15)
		f = tmp[1] ^ tmp[2] ^ tmp[3];
	else if ((ofs ? 63 - i : i) <= 31)
		f = (tmp[1] & tmp[2]) | ((~tmp[1]) & tmp[3]);
	else if ((ofs ? 63 - i : i) <= 47)
		f = (tmp[1] | (~tmp[2])) ^ tmp[3];
	else
		f = (tmp[1] & tmp[3]) | (tmp[2] & (~tmp[3]));
	f = rotate_left32(f + g_ripemd256_k[(ofs ? 64 + i : i) / 16] + tmp[0]
			+ ctx->data[g_ripemd256_g[ofs ? 64 + i : i]],
			g_ripemd256_s[ofs ? 64 + i : i]);
	tmp[0] = tmp[3];
	tmp[3] = tmp[2];
	tmp[2] = tmp[1];
	tmp[1] = f;
}

static void	ripemd256_chunk(t_ripemd256_ctx *ctx)
{
	uint32_t	tmp[8];
	int			i;

	ft_memcpy(tmp, ctx->h, 32);
	i = -1;
	while (++i < 64)
	{
		ripemd256_loop(ctx, i, tmp, 0);
		ripemd256_loop(ctx, i, tmp + 4, 1);
		if (i == 15)
			uint32_swap(&tmp[0], &tmp[4]);
		else if (i == 31)
			uint32_swap(&tmp[1], &tmp[5]);
		else if (i == 47)
			uint32_swap(&tmp[2], &tmp[6]);
		else if (i == 63)
			uint32_swap(&tmp[3], &tmp[7]);
	}
	i = -1;
	while (++i < 8)
		ctx->h[i] += tmp[i];
}

int			ripemd256_init(t_ripemd256_ctx *ctx)
{
	ctx->total_len = 0;
	ctx->data_len = 0;
	ctx->h[0] = 0x67452301;
	ctx->h[1] = 0xefcdab89;
	ctx->h[2] = 0x98badcfe;
	ctx->h[3] = 0x10325476;
	ctx->h[4] = 0x76543210;
	ctx->h[5] = 0xfedcba98;
	ctx->h[6] = 0x89abcdef;
	ctx->h[7] = 0x01234567;
	return (1);
}

int			ripemd256_update(t_ripemd256_ctx *ctx, const uint8_t *data
		, size_t len)
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
		ripemd256_chunk(ctx);
	}
	return (1);
}

int			ripemd256_final(uint8_t *md, t_ripemd256_ctx *ctx)
{
	((char*)ctx->data)[ctx->data_len] = 0x80;
	ctx->data_len++;
	if (ctx->data_len > 56)
	{
		while (ctx->data_len < 64)
			((char*)ctx->data)[ctx->data_len++] = 0;
		ripemd256_update(ctx, NULL, 0);
	}
	ft_memset(((uint8_t*)ctx->data) + ctx->data_len, 0, 64 - ctx->data_len);
	ctx->data_len = 64;
	ctx->total_len *= 8;
	ctx->data[14] = ctx->total_len;
	ripemd256_update(ctx, NULL, 0);
	ft_memcpy(md, ctx->h, 32);
	return (1);
}
