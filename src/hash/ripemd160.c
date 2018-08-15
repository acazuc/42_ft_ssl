/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripemd160.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:56:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 14:50:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/ripemd160.h"
#include "ft_ssl.h"
#include <stdio.h>

t_hash		g_hash_ripemd160 = {(t_hash_init)&ripemd160_init
		, (t_hash_update)&ripemd160_update, (t_hash_final)&ripemd160_final
		, 20, 64, sizeof(t_ripemd160_ctx), "RIPEMD160"};

static uint8_t	g_ripemd160_g[160] = {
			0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
			0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
			0x7, 0x4, 0xd, 0x1, 0xa, 0x6, 0xf, 0x3,
			0xc, 0x0, 0x9, 0x5, 0x2, 0xe, 0xb, 0x8,
			0x3, 0xa, 0xe, 0x4, 0x9, 0xf, 0x8, 0x1,
			0x2, 0x7, 0x0, 0x6, 0xd, 0xb, 0x5, 0xc,
			0x1, 0x9, 0xb, 0xa, 0x0, 0x8, 0xc, 0x4,
			0xd, 0x3, 0x7, 0xf, 0xe, 0x5, 0x6, 0x2,
			0x4, 0x0, 0x5, 0x9, 0x7, 0xc, 0x2, 0xa,
			0xe, 0x1, 0x3, 0x8, 0xb, 0x6, 0xf, 0xd,
			0x5, 0xe, 0x7, 0x0, 0x9, 0x2, 0xb, 0x4,
			0xd, 0x6, 0xf, 0x8, 0x1, 0xa, 0x3, 0xc,
			0x6, 0xb, 0x3, 0x7, 0x0, 0xd, 0x5, 0xa,
			0xe, 0xf, 0x8, 0xc, 0x4, 0x9, 0x1, 0x2,
			0xf, 0x5, 0x1, 0x3, 0x7, 0xe, 0x6, 0x9,
			0xb, 0x8, 0xc, 0x2, 0xa, 0x0, 0x4, 0xd,
			0x8, 0x6, 0x4, 0x1, 0x3, 0xb, 0xf, 0x0,
			0x5, 0xc, 0x2, 0xd, 0x9, 0x7, 0xa, 0xe,
			0xc, 0xf, 0xa, 0x4, 0x1, 0x5, 0x8, 0x7,
			0x6, 0x2, 0xd, 0xe, 0x0, 0x3, 0x9, 0xb};

static uint8_t	g_ripemd160_s[160] = {
			0xb, 0xe, 0xf, 0xc, 0x5, 0x8, 0x7, 0x9,
			0xb, 0xd, 0xe, 0xf, 0x6, 0x7, 0x9, 0x8,
			0x7, 0x6, 0x8, 0xd, 0xb, 0x9, 0x7, 0xf,
			0x7, 0xc, 0xf, 0x9, 0xb, 0x7, 0xd, 0xc,
			0xb, 0xd, 0x6, 0x7, 0xe, 0x9, 0xd, 0xf,
			0xe, 0x8, 0xd, 0x6, 0x5, 0xc, 0x7, 0x5,
			0xb, 0xc, 0xe, 0xf, 0xe, 0xf, 0x9, 0x8,
			0x9, 0xe, 0x5, 0x6, 0x8, 0x6, 0x5, 0xc,
			0x9, 0xf, 0x5, 0xb, 0x6, 0x8, 0xd, 0xc,
			0x5, 0xc, 0xd, 0xe, 0xb, 0x8, 0x5, 0x6,
			0x8, 0x9, 0x9, 0xb, 0xd, 0xf, 0xf, 0x5,
			0x7, 0x7, 0x8, 0xb, 0xe, 0xe, 0xc, 0x6,
			0x9, 0xd, 0xf, 0x7, 0xc, 0x8, 0x9, 0xb,
			0x7, 0x7, 0xc, 0x7, 0x6, 0xf, 0xd, 0xb,
			0x9, 0x7, 0xf, 0xb, 0x8, 0x6, 0x6, 0xe,
			0xc, 0xd, 0x5, 0xe, 0xd, 0xd, 0x7, 0x5,
			0xf, 0x5, 0x8, 0xb, 0xe, 0xe, 0x6, 0xe,
			0x6, 0x9, 0xc, 0x9, 0xc, 0x5, 0xf, 0x8,
			0x8, 0x5, 0xc, 0x9, 0xc, 0x5, 0xe, 0x6,
			0x8, 0xd, 0x6, 0x5, 0xf, 0xd, 0xb, 0xb};

static uint32_t	g_ripemd160_k[10] = {
		0x00000000, 0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xa953fd4e,
		0x50a28be6, 0x5c4dd124, 0x6d703ef3, 0x7a6d76e9, 0x00000000};

static void	ripemd160_loop(t_ripemd160_ctx *ctx, int i, uint32_t *tmp, int ofs)
{
	uint32_t	f;

	if ((ofs ? 79 - i : i) <= 15)
		f = tmp[1] ^ tmp[2] ^ tmp[3];
	else if ((ofs ? 79 - i : i) <= 31)
		f = (tmp[1] & tmp[2]) | ((~tmp[1]) & tmp[3]);
	else if ((ofs ? 79 - i : i) <= 47)
		f = (tmp[1] | (~tmp[2])) ^ tmp[3];
	else if ((ofs ? 79 - i : i) <= 63)
		f = (tmp[1] & tmp[3]) | (tmp[2] & (~tmp[3]));
	else
		f = tmp[1] ^ (tmp[2] | (~tmp[3]));
	f = rotate_left32(f + g_ripemd160_k[(ofs ? 80 + i : i) / 16] + tmp[0]
			+ ctx->data[g_ripemd160_g[ofs ? 80 + i : i]]
			, g_ripemd160_s[ofs ? 80 + i : i]) + tmp[4];
	tmp[0] = tmp[4];
	tmp[4] = tmp[3];
	tmp[3] = rotate_left32(tmp[2], 10);
	tmp[2] = tmp[1];
	tmp[1] = f;
}

static void	ripemd160_chunk(t_ripemd160_ctx *ctx)
{
	uint32_t	tmp[10];
	int		i;

	ft_memcpy(tmp, ctx->h, 20);
	ft_memcpy(tmp + 5, ctx->h, 20);
	i = -1;
	while (++i < 80)
	{
		ripemd160_loop(ctx, i, tmp, 0);
		ripemd160_loop(ctx, i, tmp + 5, 1);
	}
	tmp[8] += ctx->h[1] + tmp[2];
	ctx->h[1] = ctx->h[2] + tmp[3] + tmp[9];
	ctx->h[2] = ctx->h[3] + tmp[4] + tmp[5];
	ctx->h[3] = ctx->h[4] + tmp[0] + tmp[6];
	ctx->h[4] = ctx->h[0] + tmp[1] + tmp[7];
	ctx->h[0] = tmp[8];
}

int		ripemd160_init(t_ripemd160_ctx *ctx)
{
	ctx->total_len = 0;
	ctx->data_len = 0;
	ctx->h[0] = 0x67452301;
	ctx->h[1] = 0xefcdab89;
	ctx->h[2] = 0x98badcfe;
	ctx->h[3] = 0x10325476;
	ctx->h[4] = 0xc3d2e1f0;
	return (1);
}

int		ripemd160_update(t_ripemd160_ctx *ctx, const uint8_t *data, size_t len)
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
		ripemd160_chunk(ctx);
	}
	return (1);
}

int		ripemd160_final(uint8_t *md, t_ripemd160_ctx *ctx)
{
	((char*)ctx->data)[ctx->data_len] = 0x80;
	ctx->data_len++;
	if (ctx->data_len > 56)
	{
		while (ctx->data_len < 64)
			((char*)ctx->data)[ctx->data_len++] = 0;
		ripemd160_update(ctx, NULL, 0);
	}
	ft_memset(((uint8_t*)ctx->data) + ctx->data_len, 0, 64 - ctx->data_len);
	ctx->data_len = 64;
	ctx->total_len *= 8;
	ctx->data[14] = ctx->total_len;
	ripemd160_update(ctx, NULL, 0);
	ft_memcpy(md, ctx->h, 20);
	return (1);
}
