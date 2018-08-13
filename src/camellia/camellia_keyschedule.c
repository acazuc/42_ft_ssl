/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia_keyschedule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:57:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 19:21:16 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "libft.h"

static uint64_t	g_sigma1 = 0xa09e667f3bcc908bull;
static uint64_t	g_sigma2 = 0xb67ae8584caa73b2ull;
static uint64_t	g_sigma3 = 0xc6ef372fe94f82beull;
static uint64_t	g_sigma4 = 0x54ff53a5f1d36f1cull;
static uint64_t	g_sigma5 = 0x10e527fade682d1dull;
static uint64_t	g_sigma6 = 0xb05688c2b3e6c1fdull;

static void	fill_kl_kr(uint8_t *kl, uint8_t *kr, uint8_t *key, uint8_t len)
{
	*(uint64_t*)kl = ft_swap_ulong(*(uint64_t*)key);
	*(uint64_t*)(kl + 8) = ft_swap_ulong(*(uint64_t*)(key + 8));
	if (len == 16)
	{
		ft_memset(kr, 0, 16);
	}
	else if (len == 24)
	{
		*(uint64_t*)kr = ft_swap_ulong(*(uint64_t*)(key + 16));
		*(uint64_t*)(kr + 8) = ~ft_swap_ulong(*(uint64_t*)(key + 16));
	}
	else
	{
		*(uint64_t*)kr = ft_swap_ulong(*(uint64_t*)(key + 16));
		*(uint64_t*)(kr + 8) = ft_swap_ulong(*(uint64_t*)(key + 24));
	}
}

static void	fill_ka(uint8_t *ka, uint8_t *kl, uint8_t *kr)
{
	uint64_t	d1;
	uint64_t	d2;

	d1 = *(uint64_t*)kl ^ *(uint64_t*)kr;
	d2 = *(uint64_t*)(kl + 8) ^ *(uint64_t*)(kr + 8);
	d2 ^= camellia_f(d1, g_sigma1);
	d1 ^= camellia_f(d2, g_sigma2);
	d1 ^= *(uint64_t*)kl;
	d2 ^= *(uint64_t*)(kl + 8);
	d2 ^= camellia_f(d1, g_sigma3);
	d1 ^= camellia_f(d2, g_sigma4);
	ft_memcpy(ka, &d1, 8);
	ft_memcpy(ka + 8, &d2, 8);
}

static void	fill_kb(uint8_t *kb, uint8_t *ka, uint8_t *kr)
{
	uint64_t	d1;
	uint64_t	d2;

	d1 = *(uint64_t*)ka ^ *(uint64_t*)kr;
	d2 = *(uint64_t*)(ka + 8) ^ *(uint64_t*)(kr + 8);
	d2 ^= camellia_f(d1, g_sigma5);
	d1 ^= camellia_f(d2, g_sigma6);
	ft_memcpy(kb, &d1, 8);
	ft_memcpy(kb + 8, &d2, 8);
}

static	void	rot_key(uint8_t *dst, uint8_t *src, uint8_t rot)
{
	uint8_t	i;
	uint8_t	a;

	i = 0;
	while (i < 16)
	{
		a = (16 + i - rot / 8) % 16;
		dst[i] = src[a] << (rot % 8);
		a += 15;
		dst[i] |= src[a % 16] >> (8 - (rot % 8));
		++i;
	}
}

void		camellia_keyschedule(t_camellia_ctx *ctx, uint8_t *key, uint8_t len)
{
	uint8_t	tmp[16];
	uint8_t	kl[16];
	uint8_t	kr[16];
	uint8_t	ka[16];
	uint8_t	kb[16];

	fill_kl_kr(kl, kr, key, len);
	fill_ka(ka, kl, kr);
	if (len != 16)
		fill_kb(kb, ka, kr);
	if (len == 16)
	{
		rot_key(tmp, kl, 0);
		ft_memcpy(&ctx->kw[0], tmp, 8);
		ft_memcpy(&ctx->kw[1], tmp + 8, 8);
		rot_key(tmp, ka, 0);
		ft_memcpy(&ctx->k[0], tmp, 8);
		ft_memcpy(&ctx->k[1], tmp + 8, 8);
		rot_key(tmp, kl, 15);
		ft_memcpy(&ctx->k[2], tmp, 8);
		ft_memcpy(&ctx->k[3], tmp + 8, 8);
		rot_key(tmp, ka, 15);
		ft_memcpy(&ctx->k[4], tmp, 8);
		ft_memcpy(&ctx->k[5], tmp + 8, 8);
		rot_key(tmp, ka, 30);
		ft_memcpy(&ctx->ke[0], tmp, 8);
		ft_memcpy(&ctx->ke[1], tmp + 8, 8);
		rot_key(tmp, kl, 45);
		ft_memcpy(&ctx->k[6], tmp, 8);
		ft_memcpy(&ctx->k[7], tmp + 8, 8);
		rot_key(tmp, ka, 45);
		ft_memcpy(&ctx->k[8], tmp, 8);
		rot_key(tmp, kl, 60);
		ft_memcpy(&ctx->k[9], tmp + 8, 8);
		rot_key(tmp, ka, 60);
		ft_memcpy(&ctx->k[10], tmp, 8);
		ft_memcpy(&ctx->k[11], tmp + 8, 8);
		rot_key(tmp, kl, 77);
		ft_memcpy(&ctx->ke[2], tmp, 8);
		ft_memcpy(&ctx->ke[3], tmp + 8, 8);
		rot_key(tmp, kl, 94);
		ft_memcpy(&ctx->k[12], tmp, 8);
		ft_memcpy(&ctx->k[13], tmp + 8, 8);
		rot_key(tmp, ka, 94);
		ft_memcpy(&ctx->k[14], tmp, 8);
		ft_memcpy(&ctx->k[15], tmp + 8, 8);
		rot_key(tmp, kl, 111);
		ft_memcpy(&ctx->k[16], tmp, 8);
		ft_memcpy(&ctx->k[17], tmp + 8, 8);
		rot_key(tmp, ka, 111);
		ft_memcpy(&ctx->kw[2], tmp, 8);
		ft_memcpy(&ctx->kw[3], tmp + 8, 8);
	}
	else
	{
		rot_key(tmp, kl, 0);
		ft_memcpy(&ctx->kw[0], tmp, 8);
		ft_memcpy(&ctx->kw[1], tmp + 8, 8);
		rot_key(tmp, kb, 0);
		ft_memcpy(&ctx->k[0], tmp, 8);
		ft_memcpy(&ctx->k[1], tmp + 8, 8);
		rot_key(tmp, kr, 15);
		ft_memcpy(&ctx->k[2], tmp, 8);
		ft_memcpy(&ctx->k[3], tmp + 8, 8);
		rot_key(tmp, ka, 15);
		ft_memcpy(&ctx->k[4], tmp, 8);
		ft_memcpy(&ctx->k[5], tmp + 8, 8);
		rot_key(tmp, kr, 30);
		ft_memcpy(&ctx->ke[0], tmp, 8);
		ft_memcpy(&ctx->ke[1], tmp + 8, 8);
		rot_key(tmp, kb, 30);
		ft_memcpy(&ctx->k[6], tmp, 8);
		ft_memcpy(&ctx->k[7], tmp + 8, 8);
		rot_key(tmp, kl, 45);
		ft_memcpy(&ctx->k[8], tmp, 8);
		ft_memcpy(&ctx->k[9], tmp + 8, 8);
		rot_key(tmp, ka, 45);
		ft_memcpy(&ctx->k[10], tmp, 8);
		ft_memcpy(&ctx->k[11], tmp + 8, 8);
		rot_key(tmp, kl, 60);
		ft_memcpy(&ctx->ke[2], tmp, 8);
		ft_memcpy(&ctx->ke[3], tmp + 8, 8);
		rot_key(tmp, kr, 60);
		ft_memcpy(&ctx->k[12], tmp, 8);
		ft_memcpy(&ctx->k[13], tmp + 8, 8);
		rot_key(tmp, kb, 60);
		ft_memcpy(&ctx->k[14], tmp, 8);
		ft_memcpy(&ctx->k[15], tmp + 8, 8);
		rot_key(tmp, kl, 77);
		ft_memcpy(&ctx->k[16], tmp, 8);
		ft_memcpy(&ctx->k[17], tmp + 8, 8);
		rot_key(tmp, ka, 77);
		ft_memcpy(&ctx->ke[4], tmp, 8);
		ft_memcpy(&ctx->ke[5], tmp + 8, 8);
		rot_key(tmp, kr, 94);
		ft_memcpy(&ctx->k[18], tmp, 8);
		ft_memcpy(&ctx->k[19], tmp + 8, 8);
		rot_key(tmp, ka, 94);
		ft_memcpy(&ctx->k[20], tmp, 8);
		ft_memcpy(&ctx->k[21], tmp + 8, 8);
		rot_key(tmp, kl, 111);
		ft_memcpy(&ctx->k[22], tmp, 8);
		ft_memcpy(&ctx->k[23], tmp + 8, 8);
		rot_key(tmp, kb, 111);
		ft_memcpy(&ctx->kw[2], tmp, 8);
		ft_memcpy(&ctx->kw[3], tmp + 8, 8);
	}
}
