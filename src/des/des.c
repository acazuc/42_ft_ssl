/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 18:43:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:41:27 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "ft_ssl.h"

static uint8_t	g_rots[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

static uint8_t	g_pc1[56] = {
	0x39, 0x31, 0x29, 0x21, 0x19, 0x11, 0x09, 0x01,
	0x3a, 0x32, 0x2a, 0x22, 0x1a, 0x12, 0x0a, 0x02,
	0x3b, 0x33, 0x2b, 0x23, 0x1b, 0x13, 0x0b, 0x03,
	0x3c, 0x34, 0x2c, 0x24, 0x3f, 0x37, 0x2f, 0x27,
	0x1f, 0x17, 0x0f, 0x07, 0x3e, 0x36, 0x2e, 0x26,
	0x1e, 0x16, 0x0e, 0x06, 0x3d, 0x35, 0x2d, 0x25,
	0x1d, 0x15, 0x0d, 0x05, 0x1c, 0x14, 0x0c, 0x04};

static uint8_t	g_pc2[48] = {
	0x0e, 0x11, 0x0b, 0x18, 0x01, 0x05, 0x03, 0x1c,
	0x0f, 0x06, 0x15, 0x0a, 0x17, 0x13, 0x0c, 0x04,
	0x1a, 0x08, 0x10, 0x07, 0x1b, 0x14, 0x0d, 0x02,
	0x29, 0x34, 0x1f, 0x25, 0x2f, 0x37, 0x1e, 0x28,
	0x33, 0x2d, 0x21, 0x30, 0x2c, 0x31, 0x27, 0x38,
	0x22, 0x35, 0x2e, 0x2a, 0x32, 0x24, 0x1d, 0x20};

static uint8_t	g_ip[64] = {
	0x3a, 0x32, 0x2a, 0x22, 0x1a, 0x12, 0x0a, 0x02,
	0x3c, 0x34, 0x2c, 0x24, 0x1c, 0x14, 0x0c, 0x04,
	0x3e, 0x36, 0x2e, 0x26, 0x1e, 0x16, 0x0e, 0x06,
	0x40, 0x38, 0x30, 0x28, 0x20, 0x18, 0x10, 0x08,
	0x39, 0x31, 0x29, 0x21, 0x19, 0x11, 0x09, 0x01,
	0x3b, 0x33, 0x2b, 0x23, 0x1b, 0x13, 0x0b, 0x03,
	0x3d, 0x35, 0x2d, 0x25, 0x1d, 0x15, 0x0d, 0x05,
	0x3f, 0x37, 0x2f, 0x27, 0x1f, 0x17, 0x0f, 0x07};

static uint8_t	g_ip1[64] = {
	0x28, 0x08, 0x30, 0x10, 0x38, 0x18, 0x40, 0x20,
	0x27, 0x07, 0x2f, 0x0f, 0x37, 0x17, 0x3f, 0x1f,
	0x26, 0x06, 0x2e, 0x0e, 0x36, 0x16, 0x3e, 0x1e,
	0x25, 0x05, 0x2d, 0x0d, 0x35, 0x15, 0x3d, 0x1d,
	0x24, 0x04, 0x2c, 0x0c, 0x34, 0x14, 0x3c, 0x1c,
	0x23, 0x03, 0x2b, 0x0b, 0x33, 0x13, 0x3b, 0x1b,
	0x22, 0x02, 0x2a, 0x0a, 0x32, 0x12, 0x3a, 0x1a,
	0x21, 0x01, 0x29, 0x09, 0x31, 0x11, 0x39, 0x19};

static uint8_t	g_e[48] = {
	0x20, 0x01, 0x02, 0x03, 0x04, 0x05, 0x04, 0x05,
	0x06, 0x07, 0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x14, 0x15,
	0x16, 0x17, 0x18, 0x19, 0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x01};

static uint8_t	g_p[32] = {
	0x10, 0x07, 0x14, 0x15, 0x1d, 0x0c, 0x1c, 0x11,
	0x01, 0x0f, 0x17, 0x1a, 0x05, 0x12, 0x1f, 0x0a,
	0x02, 0x08, 0x18, 0x0e, 0x20, 0x1b, 0x03, 0x09,
	0x13, 0x0d, 0x1e, 0x06, 0x16, 0x0b, 0x04, 0x19};

static uint8_t	g_ss[8][64] = {
	{
		0xe, 0x4, 0xd, 0x1, 0x2, 0xf, 0xb, 0x8,
		0x3, 0xa, 0x6, 0xc, 0x5, 0x9, 0x0, 0x7,
		0x0, 0xf, 0x7, 0x4, 0xe, 0x2, 0xd, 0x1,
		0xa, 0x6, 0xc, 0xb, 0x9, 0x5, 0x3, 0x8,
		0x4, 0x1, 0xe, 0x8, 0xd, 0x6, 0x2, 0xb,
		0xf, 0xc, 0x9, 0x7, 0x3, 0xa, 0x5, 0x0,
		0xf, 0xc, 0x8, 0x2, 0x4, 0x9, 0x1, 0x7,
		0x5, 0xb, 0x3, 0xe, 0xa, 0x0, 0x6, 0xd
	},
	{
		0xf, 0x1, 0x8, 0xe, 0x6, 0xb, 0x3, 0x4,
		0x9, 0x7, 0x2, 0xd, 0xc, 0x0, 0x5, 0xa,
		0x3, 0xd, 0x4, 0x7, 0xf, 0x2, 0x8, 0xe,
		0xc, 0x0, 0x1, 0xa, 0x6, 0x9, 0xb, 0x5,
		0x0, 0xe, 0x7, 0xb, 0xa, 0x4, 0xd, 0x1,
		0x5, 0x8, 0xc, 0x6, 0x9, 0x3, 0x2, 0xf,
		0xd, 0x8, 0xa, 0x1, 0x3, 0xf, 0x4, 0x2,
		0xb, 0x6, 0x7, 0xc, 0x0, 0x5, 0xe, 0x9
	},
	{
		0xa, 0x0, 0x9, 0xe, 0x6, 0x3, 0xf, 0x5,
		0x1, 0xd, 0xc, 0x7, 0xb, 0x4, 0x2, 0x8,
		0xd, 0x7, 0x0, 0x9, 0x3, 0x4, 0x6, 0xa,
		0x2, 0x8, 0x5, 0xe, 0xc, 0xb, 0xf, 0x1,
		0xd, 0x6, 0x4, 0x9, 0x8, 0xf, 0x3, 0x0,
		0xb, 0x1, 0x2, 0xc, 0x5, 0xa, 0xe, 0x7,
		0x1, 0xa, 0xd, 0x0, 0x6, 0x9, 0x8, 0x7,
		0x4, 0xf, 0xe, 0x3, 0xb, 0x5, 0x2, 0xc
	},
	{
		0x7, 0xd, 0xe, 0x3, 0x0, 0x6, 0x9, 0xa,
		0x1, 0x2, 0x8, 0x5, 0xb, 0xc, 0x4, 0xf,
		0xd, 0x8, 0xb, 0x5, 0x6, 0xf, 0x0, 0x3,
		0x4, 0x7, 0x2, 0xc, 0x1, 0xa, 0xe, 0x9,
		0xa, 0x6, 0x9, 0x0, 0xc, 0xb, 0x7, 0xd,
		0xf, 0x1, 0x3, 0xe, 0x5, 0x2, 0x8, 0x4,
		0x3, 0xf, 0x0, 0x6, 0xa, 0x1, 0xd, 0x8,
		0x9, 0x4, 0x5, 0xb, 0xc, 0x7, 0x2, 0xe
	},
	{
		0x2, 0xc, 0x4, 0x1, 0x7, 0xa, 0xb, 0x6,
		0x8, 0x5, 0x3, 0xf, 0xd, 0x0, 0xe, 0x9,
		0xe, 0xb, 0x2, 0xc, 0x4, 0x7, 0xd, 0x1,
		0x5, 0x0, 0xf, 0xa, 0x3, 0x9, 0x8, 0x6,
		0x4, 0x2, 0x1, 0xb, 0xa, 0xd, 0x7, 0x8,
		0xf, 0x9, 0xc, 0x5, 0x6, 0x3, 0x0, 0xe,
		0xb, 0x8, 0xc, 0x7, 0x1, 0xe, 0x2, 0xd,
		0x6, 0xf, 0x0, 0x9, 0xa, 0x4, 0x5, 0x3
	},
	{
		0xc, 0x1, 0xa, 0xf, 0x9, 0x2, 0x6, 0x8,
		0x0, 0xd, 0x3, 0x4, 0xe, 0x7, 0x5, 0xb,
		0xa, 0xf, 0x4, 0x2, 0x7, 0xc, 0x9, 0x5,
		0x6, 0x1, 0xd, 0xe, 0x0, 0xb, 0x3, 0x8,
		0x9, 0xe, 0xf, 0x5, 0x2, 0x8, 0xc, 0x3,
		0x7, 0x0, 0x4, 0xa, 0x1, 0xd, 0xb, 0x6,
		0x4, 0x3, 0x2, 0xc, 0x9, 0x5, 0xf, 0xa,
		0xb, 0xe, 0x1, 0x7, 0x6, 0x0, 0x8, 0xd
	},
	{
		0x4, 0xb, 0x2, 0xe, 0xf, 0x0, 0x8, 0xd,
		0x3, 0xc, 0x9, 0x7, 0x5, 0xa, 0x6, 0x1,
		0xd, 0x0, 0xb, 0x7, 0x4, 0x9, 0x1, 0xa,
		0xe, 0x3, 0x5, 0xc, 0x2, 0xf, 0x8, 0x6,
		0x1, 0x4, 0xb, 0xd, 0xc, 0x3, 0x7, 0xe,
		0xa, 0xf, 0x6, 0x8, 0x0, 0x5, 0x9, 0x2,
		0x6, 0xb, 0xd, 0x8, 0x1, 0x4, 0xa, 0x7,
		0x9, 0x5, 0x0, 0xf, 0xe, 0x2, 0x3, 0xc
	},
	{
		0xd, 0x2, 0x8, 0x4, 0x6, 0xf, 0xb, 0x1,
		0xa, 0x9, 0x3, 0xe, 0x5, 0x0, 0xc, 0x7,
		0x1, 0xf, 0xd, 0x8, 0xa, 0x3, 0x7, 0x4,
		0xc, 0x5, 0x6, 0xb, 0x0, 0xe, 0x9, 0x2,
		0x7, 0xb, 0x4, 0x1, 0x9, 0xc, 0xe, 0x2,
		0x0, 0x6, 0xa, 0xd, 0xf, 0x3, 0x5, 0x8,
		0x2, 0x1, 0xe, 0x7, 0x4, 0xa, 0x8, 0xd,
		0xf, 0xc, 0x9, 0x0, 0x3, 0x5, 0x6, 0xb
	}};

static uint64_t	des_permute(uint64_t src, const uint8_t *table
		, uint8_t out_len, uint8_t in_len)
{
	uint64_t	result;
	int			i;

	result = 0;
	i = 0;
	while (i < out_len)
	{
		result |= ((src >> ((in_len - 1) - (table[i] - 1))) & 1)
			<< ((out_len - 1) - i);
		++i;
	}
	return (result);
}

void			des_generate_keys(t_des_ctx *ctx, uint64_t key)
{
	uint64_t	tmp;
	uint64_t	dst;
	uint32_t	c[16];
	uint32_t	d[16];
	int			i;

	dst = des_permute(key, g_pc1, 56, 64);
	c[0] = rotate_left28((dst & 0xfffffff0000000) >> 28, g_rots[0]) & 0xfffffff;
	d[0] = rotate_left28(dst & 0xfffffff, g_rots[0]) & 0xfffffff;
	i = 1;
	while (i < 16)
	{
		c[i] = rotate_left28(c[i - 1], g_rots[i]) & 0xfffffff;
		d[i] = rotate_left28(d[i - 1], g_rots[i]) & 0xfffffff;
		++i;
	}
	i = 0;
	while (i < 16)
	{
		tmp = (uint64_t)d[i] | ((uint64_t)c[i] << 28);
		ctx->keys[i] = des_permute(tmp, g_pc2, 48, 56);
		++i;
	}
}

static uint32_t	des_f(uint32_t r, uint64_t key)
{
	uint64_t	tmp;
	uint32_t	res;
	uint8_t		s;
	int			i;

	tmp = des_permute(r, g_e, 48, 32);
	tmp ^= key;
	res = 0;
	i = 0;
	while (i < 8)
	{
		s = (tmp >> (6 * (7 - i))) & 0x3f;
		s = g_ss[i][((s & 0x20) | ((s & 1) << 4)) + ((s >> 1) & 0xf)];
		res |= s << ((7 - i) * 4);
		++i;
	}
	tmp = des_permute(res, g_p, 32, 32);
	return (tmp);
}

void			des_operate_block(t_des_ctx *ctx, uint64_t *block, int mode)
{
	uint64_t	tmp;
	uint32_t	l[16];
	uint32_t	r[16];
	int			i;

	tmp = des_permute(ft_swap_ulong(*block), g_ip, 64, 64);
	l[0] = tmp & 0xffffffff;
	r[0] = (tmp >> 32) ^ des_f(l[0], ctx->keys[mode ? 15 : 0]);
	i = 1;
	while (i < 16)
	{
		l[i] = r[i - 1];
		r[i] = l[i - 1] ^ des_f(r[i - 1], ctx->keys[mode ? 15 - i : i]);
		++i;
	}
	tmp = ((uint64_t)r[15] << 32) | (uint64_t)l[15];
	*block = ft_swap_ulong(des_permute(tmp, g_ip1, 64, 64));
}
