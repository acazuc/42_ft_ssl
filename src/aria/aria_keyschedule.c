/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aria_keyschedule.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:32:53 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 16:22:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"
#include "ft_ssl.h"

static uint8_t	c1[16] = {
	0x51, 0x7c, 0xc1, 0xb7, 0x27, 0x22, 0x0a, 0x94,
	0xfe, 0x13, 0xab, 0xe8, 0xfa, 0x9a, 0x6e, 0xe0};

static uint8_t	c2[16] = {
	0x6d, 0xb1, 0x4a, 0xcc, 0x9e, 0x21, 0xc8, 0x20,
	0xff, 0x28, 0xb1, 0xd5, 0xef, 0x5d, 0xe2, 0xb0};

static uint8_t	c3[16] = {
	0xdb, 0x92, 0x37, 0x1d, 0x21, 0x26, 0xe9, 0x70,
	0x03, 0x24, 0x97, 0x75, 0x04, 0xe8, 0xc9, 0x0e};

static uint8_t	*ck128[3] = {c1, c2, c3};
static uint8_t	*ck192[3] = {c2, c3, c1};
static uint8_t	*ck256[3] = {c3, c1, c2};

static void	setekeys2(t_aria_ctx *ctx, uint8_t w[4][16], uint8_t keylen)
{
	uint8_t	tmp[16];

	rotate_leftn(tmp, w[0], 61, 16);
	ft_memxor(ctx->ekeys[0xb], tmp, w[3], 16);
	rotate_leftn(tmp, w[1], 31, 16);
	ft_memxor(ctx->ekeys[0xc], tmp, w[0], 16);
	if (keylen >= 24)
	{
		rotate_leftn(tmp, w[2], 31, 16);
		ft_memxor(ctx->ekeys[0xd], tmp, w[1], 16);
		rotate_leftn(tmp, w[3], 31, 16);
		ft_memxor(ctx->ekeys[0xe], tmp, w[2], 16);
		if (keylen == 32)
		{
			rotate_leftn(tmp, w[0], 31, 16);
			ft_memxor(ctx->ekeys[0xf], tmp, w[3], 16);
			rotate_leftn(tmp, w[1], 19, 16);
			ft_memxor(ctx->ekeys[0x10], tmp, w[0], 16);
		}
	}
}

static void	setekeys(t_aria_ctx *ctx, uint8_t w[4][16], uint8_t keylen)
{
	uint8_t	tmp[16];

	rotate_rightn(tmp, w[1], 19, 16);
	ft_memxor(ctx->ekeys[0x0], tmp, w[0], 16);
	rotate_rightn(tmp, w[2], 19, 16);
	ft_memxor(ctx->ekeys[0x1], tmp, w[1], 16);
	rotate_rightn(tmp, w[3], 19, 16);
	ft_memxor(ctx->ekeys[0x2], tmp, w[2], 16);
	rotate_rightn(tmp, w[0], 19, 16);
	ft_memxor(ctx->ekeys[0x3], tmp, w[3], 16);
	rotate_rightn(tmp, w[1], 31, 16);
	ft_memxor(ctx->ekeys[0x4], tmp, w[0], 16);
	rotate_rightn(tmp, w[2], 31, 16);
	ft_memxor(ctx->ekeys[0x5], tmp, w[1], 16);
	rotate_rightn(tmp, w[3], 31, 16);
	ft_memxor(ctx->ekeys[0x6], tmp, w[2], 16);
	rotate_rightn(tmp, w[0], 31, 16);
	ft_memxor(ctx->ekeys[0x7], tmp, w[3], 16);
	rotate_leftn(tmp, w[1], 61, 16);
	ft_memxor(ctx->ekeys[0x8], tmp, w[0], 16);
	rotate_leftn(tmp, w[2], 61, 16);
	ft_memxor(ctx->ekeys[0x9], tmp, w[1], 16);
	rotate_leftn(tmp, w[3], 61, 16);
	ft_memxor(ctx->ekeys[0xa], tmp, w[2], 16);
	setekeys2(ctx, w, keylen);
}

static void	setdkeys(t_aria_ctx *ctx, uint8_t keylen)
{
	int	rounds;
	int	i;

	if (keylen == 16)
		rounds = 12;
	else if (keylen == 24)
		rounds = 14;
	else
		rounds = 16;
	ft_memcpy(ctx->dkeys[0], ctx->ekeys[rounds], 16);
	i = 1;
	while (i < rounds)
	{
		aria_a(ctx->dkeys[i], ctx->ekeys[rounds - i]);
		++i;
	}
	ft_memcpy(ctx->dkeys[rounds], ctx->ekeys[0], 16);
}

void		aria_keyschedule(t_aria_ctx *ctx, uint8_t *key, uint8_t len)
{
	uint8_t	k[32];
	uint8_t	w[4][16];
	uint8_t **ck;

	if (len == 16)
		ck = ck128;
	else if (len == 24)
		ck = ck192;
	else
		ck = ck256;
	ft_memcpy(k, key, len);
	ft_memset(k + len, 0, 32 - len);
	ft_memcpy(w[0], k, 16);
	aria_fo(w[1], w[0], ck[0]);
	ft_memxor(w[1], w[1], k + 16, 16);
	aria_fe(w[2], w[1], ck[1]);
	ft_memxor(w[2], w[2], w[0], 16);
	aria_fo(w[3], w[2], ck[2]);
	ft_memxor(w[3], w[3], w[1], 16);
	setekeys(ctx, w, len);
	setdkeys(ctx, len);
}
