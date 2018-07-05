/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:55:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 22:07:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha224.h"

t_hash		g_hash_sha224 = {(t_hash_init)&sha224_init
		, (t_hash_update)&sha224_update, (t_hash_final)&sha224_final
		, 28, 64, "SHA224"};

static uint32_t	g_sha224_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5
			, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5
			, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3
			, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174
			, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc
			, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da
			, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7
			, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967
			, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13
			, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85
			, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3
			, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070
			, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5
			, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3
			, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208
			, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static void	sha224_loop(int i, uint32_t *tmp
		, uint32_t *w)
{
	uint32_t	tmp1;
	uint32_t	tmp2;
	uint32_t	tmp3;
	uint32_t	tmp4;

	tmp1 = rotate_right32(tmp[4], 6) ^ rotate_right32(tmp[4], 11)
		^ rotate_right32(tmp[4], 25);
	tmp2 = (tmp[4] & tmp[5]) ^ ((~tmp[4]) & tmp[6]);
	tmp3 = tmp[7] + tmp1 + tmp2 + g_sha224_k[i] + w[i];
	tmp1 = rotate_right32(tmp[0], 2) ^ rotate_right32(tmp[0], 13)
		^ rotate_right32(tmp[0], 22);
	tmp2 = (tmp[0] & tmp[1]) ^ (tmp[0] & tmp[2]) ^ (tmp[1] & tmp[2]);
	tmp4 = tmp1 + tmp2;
	tmp[7] = tmp[6];
	tmp[6] = tmp[5];
	tmp[5] = tmp[4];
	tmp[4] = tmp[3] + tmp3;
	tmp[3] = tmp[2];
	tmp[2] = tmp[1];
	tmp[1] = tmp[0];
	tmp[0] = tmp3 + tmp4;
}

static void	sha224_chunk(t_sha224_ctx *ctx)
{
	uint32_t	tmp[8];
	uint32_t	w[64];
	int		i;

	i = -1;
	while (++i < 16)
		w[i] = ft_swap_uint(ctx->data[i]);
	while (i < 64)
	{
		w[i] = w[i - 16] + (rotate_right32(w[i - 15], 7)
		^ rotate_right32(w[i - 15], 18) ^ (w[i - 15] >> 3)) + w[i - 7]
		+ (rotate_right32(w[i - 2], 17) ^ rotate_right32(w[i - 2], 19)
		^ (w[i - 2] >> 10));
		++i;
	}
	i = -1;
	while (++i < 8)
		tmp[i] = ctx->h[i];
	i = -1;
	while (++i < 64)
		sha224_loop(i, tmp, w);
	i = -1;
	while (++i < 8)
		ctx->h[i] += tmp[i];
}

int		sha224_init(t_sha224_ctx *ctx)
{
	ctx->total_len = 0;
	ctx->data_len = 0;
	ctx->h[0] = 0xc1059ed8;
	ctx->h[1] = 0x367cd507;
	ctx->h[2] = 0x3070dd17;
	ctx->h[3] = 0xf70e5939;
	ctx->h[4] = 0xffc00b31;
	ctx->h[5] = 0x68581511;
	ctx->h[6] = 0x64f98fa7;
	ctx->h[7] = 0xbefa4fa4;
	return (1);
}

int		sha224_update(t_sha224_ctx *ctx, const uint8_t *data, size_t len)
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
		sha224_chunk(ctx);
	}
	return (1);
}

int		sha224_final(uint8_t *md, t_sha224_ctx *ctx)
{
	int	i;

	((char*)ctx->data)[ctx->data_len] = 0x80;
	ctx->data_len++;
	if (ctx->data_len > 56)
	{
		while (ctx->data_len < 64)
			((char*)ctx->data)[ctx->data_len++] = 0;
		sha224_update(ctx, NULL, 0);
	}
	while (ctx->data_len < 56)
		((char*)ctx->data)[ctx->data_len++] = 0;
	ctx->total_len = ft_swap_ulong(ctx->total_len * 8);
	ft_memcpy(ctx->data + 14, &ctx->total_len, 8);
	ctx->data_len = 64;
	sha224_update(ctx, NULL, 0);
	i = -1;
	while (++i < 7)
	{
		md[i * 4 + 0] = ctx->h[i] >> 24;
		md[i * 4 + 1] = ctx->h[i] >> 16;
		md[i * 4 + 2] = ctx->h[i] >> 8;
		md[i * 4 + 3] = ctx->h[i] >> 0;
	}
	return (1);
}
