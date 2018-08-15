/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia_keyschedule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:57:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 21:29:58 by acazuc           ###   ########.fr       */
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

static void	fill_kl_kr(uint8_t *klr, uint8_t *key, uint8_t len)
{
	*(uint64_t*)(klr + 0) = ft_swap_ulong(*(uint64_t*)(key + 0));
	*(uint64_t*)(klr + 8) = ft_swap_ulong(*(uint64_t*)(key + 8));
	if (len == 16)
	{
		ft_memset(klr + 16, 0, 16);
	}
	else if (len == 24)
	{
		*(uint64_t*)(klr + 16) = ft_swap_ulong(*(uint64_t*)(key + 16));
		*(uint64_t*)(klr + 24) = ~ft_swap_ulong(*(uint64_t*)(key + 16));
	}
	else
	{
		*(uint64_t*)(klr + 16) = ft_swap_ulong(*(uint64_t*)(key + 16));
		*(uint64_t*)(klr + 24) = ft_swap_ulong(*(uint64_t*)(key + 24));
	}
}

static void	fill_ka(uint8_t *kab, uint8_t *klr)
{
	uint64_t	d1;
	uint64_t	d2;

	d1 = *(uint64_t*)(klr + 0) ^ *(uint64_t*)(klr + 16);
	d2 = *(uint64_t*)(klr + 8) ^ *(uint64_t*)(klr + 24);
	d2 ^= camellia_f(d1, g_sigma1);
	d1 ^= camellia_f(d2, g_sigma2);
	d1 ^= *(uint64_t*)(klr + 0);
	d2 ^= *(uint64_t*)(klr + 8);
	d2 ^= camellia_f(d1, g_sigma3);
	d1 ^= camellia_f(d2, g_sigma4);
	ft_memcpy(kab + 0, &d1, 8);
	ft_memcpy(kab + 8, &d2, 8);
}

static void	fill_kb(uint8_t *kab, uint8_t *klr)
{
	uint64_t	d1;
	uint64_t	d2;

	d1 = *(uint64_t*)(kab + 0) ^ *(uint64_t*)(klr + 16);
	d2 = *(uint64_t*)(kab + 8) ^ *(uint64_t*)(klr + 24);
	d2 ^= camellia_f(d1, g_sigma5);
	d1 ^= camellia_f(d2, g_sigma6);
	ft_memcpy(kab + 16, &d1, 8);
	ft_memcpy(kab + 24, &d2, 8);
}

void		camellia_keyschedule(t_camellia_ctx *ctx, uint8_t *key, uint8_t len)
{
	uint8_t	klr[32];
	uint8_t	kab[32];

	fill_kl_kr(klr, key, len);
	fill_ka(kab, klr);
	if (len != 16)
		fill_kb(kab, klr);
	if (len == 16)
		camellia_keyschedule_128(ctx, klr, kab);
	else
		camellia_keyschedule_192_256(ctx, klr, kab);
}
