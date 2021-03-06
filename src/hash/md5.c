/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:56:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 12:25:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/md5.h"
#include "ft_ssl.h"

t_hash		g_hash_md5 = {"MD5",
	(t_hash_init)md5_init,
	(t_hash_update)md5_update,
	(t_hash_final)md5_final,
	16, 64, sizeof(t_md5_ctx)};

static uint32_t	g_md5_s[64] = {
	0x07, 0x0c, 0x11, 0x16, 0x07, 0x0c, 0x11, 0x16,
	0x07, 0x0c, 0x11, 0x16, 0x07, 0x0c, 0x11, 0x16,
	0x05, 0x09, 0x0e, 0x14, 0x05, 0x09, 0x0e, 0x14,
	0x05, 0x09, 0x0e, 0x14, 0x05, 0x09, 0x0e, 0x14,
	0x04, 0x0b, 0x10, 0x17, 0x04, 0x0b, 0x10, 0x17,
	0x04, 0x0b, 0x10, 0x17, 0x04, 0x0b, 0x10, 0x17,
	0x06, 0x0a, 0x0f, 0x15, 0x06, 0x0a, 0x0f, 0x15,
	0x06, 0x0a, 0x0f, 0x15, 0x06, 0x0a, 0x0f, 0x15};

static uint32_t	g_md5_g[64] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x01, 0x06, 0x0b, 0x00, 0x05, 0x0a, 0x0f, 0x04,
	0x09, 0x0e, 0x03, 0x08, 0x0d, 0x02, 0x07, 0x0c,
	0x05, 0x08, 0x0b, 0x0e, 0x01, 0x04, 0x07, 0x0a,
	0x0d, 0x00, 0x03, 0x06, 0x09, 0x0c, 0x0f, 0x02,
	0x00, 0x07, 0x0e, 0x05, 0x0c, 0x03, 0x0a, 0x01,
	0x08, 0x0f, 0x06, 0x0d, 0x04, 0x0b, 0x02, 0x09};

static uint32_t	g_md5_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static void	md5_loop(t_md5_ctx *ctx, int i, uint32_t *tmp)
{
	uint32_t	f;

	if (i <= 15)
		f = (tmp[1] & tmp[2]) | ((~tmp[1]) & tmp[3]);
	else if (i <= 31)
		f = (tmp[3] & tmp[1]) | ((~tmp[3]) & tmp[2]);
	else if (i <= 47)
		f = tmp[1] ^ tmp[2] ^ tmp[3];
	else
		f = tmp[2] ^ (tmp[1] | (~tmp[3]));
	f += tmp[0] + g_md5_k[i] + ctx->data[g_md5_g[i]];
	tmp[0] = tmp[3];
	tmp[3] = tmp[2];
	tmp[2] = tmp[1];
	tmp[1] += rotate_left32(f, g_md5_s[i]);
}

static void	md5_chunk(t_md5_ctx *ctx)
{
	uint32_t	tmp[4];
	int			i;

	ft_memcpy(tmp, ctx->h, 16);
	i = -1;
	while (++i < 64)
		md5_loop(ctx, i, tmp);
	i = -1;
	while (++i < 4)
		ctx->h[i] += tmp[i];
}

int			md5_init(t_md5_ctx *ctx)
{
	ctx->total_len = 0;
	ctx->data_len = 0;
	ctx->h[0] = 0x67452301;
	ctx->h[1] = 0xefcdab89;
	ctx->h[2] = 0x98badcfe;
	ctx->h[3] = 0x10325476;
	return (1);
}

int			md5_update(t_md5_ctx *ctx, const uint8_t *data, size_t len)
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
		md5_chunk(ctx);
	}
	return (1);
}

int			md5_final(uint8_t *md, t_md5_ctx *ctx)
{
	((char*)ctx->data)[ctx->data_len] = 0x80;
	ctx->data_len++;
	if (ctx->data_len > 56)
	{
		while (ctx->data_len < 64)
			((char*)ctx->data)[ctx->data_len++] = 0;
		md5_update(ctx, NULL, 0);
	}
	while (ctx->data_len < 56)
		((char*)ctx->data)[ctx->data_len++] = 0;
	ctx->total_len *= 8;
	ft_memcpy(ctx->data + 14, &ctx->total_len, 8);
	ctx->data_len = 64;
	md5_update(ctx, NULL, 0);
	ft_memcpy(md, ctx->h, 16);
	return (1);
}
