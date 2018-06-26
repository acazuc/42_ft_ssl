/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 09:32:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:21:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

t_hash		g_hash_sha512 = {(t_hash_init*)sha512_init
		, (t_hash_update*)sha512_update, (t_hash_final*)sha512_final
		, 64, 128, "SHA512"};

static uint64_t g_sha512_k[128] = {0x428a2f98d728ae22, 0x7137449123ef65cd
				, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc
				, 0x3956c25bf348b538, 0x59f111f1b605d019
				, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118
				, 0xd807aa98a3030242, 0x12835b0145706fbe
				, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2
				, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1
				, 0x9bdc06a725c71235, 0xc19bf174cf692694
				, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3
				, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65
				, 0x2de92c6f592b0275, 0x4a7484aa6ea6e483
				, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5
				, 0x983e5152ee66dfab, 0xa831c66d2db43210
				, 0xb00327c898fb213f, 0xbf597fc7beef0ee4
				, 0xc6e00bf33da88fc2, 0xd5a79147930aa725
				, 0x06ca6351e003826f, 0x142929670a0e6e70
				, 0x27b70a8546d22ffc, 0x2e1b21385c26c926
				, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df
				, 0x650a73548baf63de, 0x766a0abb3c77b2a8
				, 0x81c2c92e47edaee6, 0x92722c851482353b
				, 0xa2bfe8a14cf10364, 0xa81a664bbc423001
				, 0xc24b8b70d0f89791, 0xc76c51a30654be30
				, 0xd192e819d6ef5218, 0xd69906245565a910
				, 0xf40e35855771202a, 0x106aa07032bbd1b8
				, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53
				, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8
				, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb
				, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3
				, 0x748f82ee5defb2fc, 0x78a5636f43172f60
				, 0x84c87814a1f0ab72, 0x8cc702081a6439ec
				, 0x90befffa23631e28, 0xa4506cebde82bde9
				, 0xbef9a3f7b2c67915, 0xc67178f2e372532b
				, 0xca273eceea26619c, 0xd186b8c721c0c207
				, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178
				, 0x06f067aa72176fba, 0x0a637dc5a2c898a6
				, 0x113f9804bef90dae, 0x1b710b35131c471b
				, 0x28db77f523047d84, 0x32caab7b40c72493
				, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c
				, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a
				, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

static void	sha512_loop(int i, uint64_t *tmp
		, uint64_t *w)
{
	uint64_t	tmp1;
	uint64_t	tmp2;
	uint64_t	tmp3;
	uint64_t	tmp4;

	tmp1 = rotate_right64(tmp[4], 14) ^ rotate_right64(tmp[4], 18)
		^ rotate_right64(tmp[4], 41);
	tmp2 = (tmp[4] & tmp[5]) ^ ((~tmp[4]) & tmp[6]);
	tmp3 = tmp[7] + tmp1 + tmp2 + g_sha512_k[i] + w[i];
	tmp1 = rotate_right64(tmp[0], 28) ^ rotate_right64(tmp[0], 34)
		^ rotate_right64(tmp[0], 39);
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

static void	sha512_chunk(t_sha512_ctx *ctx)
{
	uint64_t	tmp[8];
	uint64_t	w[80];
	int		i;

	i = -1;
	while (++i < 16)
		w[i] = ft_swap_ulong(ctx->data[i]);
	while (i < 80)
	{
		w[i] = w[i - 16] + (rotate_right64(w[i - 15], 1) ^ rotate_right64(
		w[i - 15], 8) ^ (w[i - 15] >> 7)) + w[i - 7]
		+ (rotate_right64(w[i - 2], 19) ^ rotate_right64(w[i - 2], 61)
		^ (w[i - 2] >> 6));
		++i;
	}
	i = -1;
	while (++i < 8)
		tmp[i] = ctx->h[i];
	i = -1;
	while (++i < 80)
		sha512_loop(i, tmp, w);
	i = -1;
	while (++i < 8)
		ctx->h[i] += tmp[i];
}

int		sha512_init(t_sha512_ctx *ctx)
{
	ctx->total_len = 0;
	ctx->data_len = 0;
	ctx->h[0] = 0x6a09e667f3bcc908;
	ctx->h[1] = 0xbb67ae8584caa73b;
	ctx->h[2] = 0x3c6ef372fe94f82b;
	ctx->h[3] = 0xa54ff53a5f1d36f1;
	ctx->h[4] = 0x510e527fade682d1;
	ctx->h[5] = 0x9b05688c2b3e6c1f;
	ctx->h[6] = 0x1f83d9abfb41bd6b;
	ctx->h[7] = 0x5be0cd19137e2179;
	return (1);
}

int		sha512_update(t_sha512_ctx *ctx, const uint8_t *data, size_t len)
{
	while (1)
	{
		if (ctx->data_len + len < 128)
		{
			ft_memcpy((char*)ctx->data + ctx->data_len, data, len);
			ctx->data_len += len;
			ctx->total_len += len;
			return (1);
		}
		ft_memcpy((char*)ctx->data + ctx->data_len, data, 128 - ctx->data_len);
		len -= 128 - ctx->data_len;
		data += 128 - ctx->data_len;
		ctx->total_len += 128 - ctx->data_len;
		ctx->data_len = 0;
		sha512_chunk(ctx);
	}
	return (1);
}

int		sha512_final(uint8_t *md, t_sha512_ctx *ctx)
{
	int	i;

	((char*)ctx->data)[ctx->data_len++] = 0x80;
	if (ctx->data_len > 112)
	{
		while (ctx->data_len < 128)
			((char*)ctx->data)[ctx->data_len++] = 0;
		sha512_update(ctx, NULL, 0);
	}
	while (ctx->data_len < 120)
		((char*)ctx->data)[ctx->data_len++] = 0;
	ctx->total_len = ft_swap_ulong(ctx->total_len * 8);
	ft_memcpy(ctx->data + 15, &ctx->total_len, 8);
	ctx->data_len = 128;
	sha512_update(ctx, NULL, 0);
	i = -1;
	while (++i < 8)
	{
		md[i * 8 + 0] = ctx->h[i] >> 56;
		md[i * 8 + 1] = ctx->h[i] >> 48;
		md[i * 8 + 2] = ctx->h[i] >> 40;
		md[i * 8 + 3] = ctx->h[i] >> 32;
		md[i * 8 + 4] = ctx->h[i] >> 24;
		md[i * 8 + 5] = ctx->h[i] >> 16;
		md[i * 8 + 6] = ctx->h[i] >> 8;
		md[i * 8 + 7] = ctx->h[i] >> 0;
	}
	return (1);
}
