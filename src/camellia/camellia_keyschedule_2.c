/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia_keyschedule_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 18:22:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 11:41:52 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "libft.h"

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

static void		ks_128_2(t_camellia_ctx *ctx, uint8_t *klr, uint8_t *kab)
{
	uint8_t	tmp[16];

	rot_key(tmp, kab + 0, 94);
	ft_memcpy(&ctx->k[14], tmp, 16);
	rot_key(tmp, klr + 0, 111);
	ft_memcpy(&ctx->k[16], tmp, 16);
	rot_key(tmp, kab + 0, 111);
	ft_memcpy(&ctx->kw[2], tmp, 16);
}

void			camellia_keyschedule_128(t_camellia_ctx *ctx, uint8_t *klr
		, uint8_t *kab)
{
	uint8_t	tmp[16];

	rot_key(tmp, klr + 0, 0);
	ft_memcpy(&ctx->kw[0], tmp, 16);
	rot_key(tmp, kab + 0, 0);
	ft_memcpy(&ctx->k[0], tmp, 16);
	rot_key(tmp, klr + 0, 15);
	ft_memcpy(&ctx->k[2], tmp, 16);
	rot_key(tmp, kab + 0, 15);
	ft_memcpy(&ctx->k[4], tmp, 16);
	rot_key(tmp, kab + 0, 30);
	ft_memcpy(&ctx->ke[0], tmp, 16);
	rot_key(tmp, klr + 0, 45);
	ft_memcpy(&ctx->k[6], tmp, 16);
	rot_key(tmp, kab + 0, 45);
	ft_memcpy(&ctx->k[8], tmp, 8);
	rot_key(tmp, klr + 0, 60);
	ft_memcpy(&ctx->k[9], tmp + 8, 8);
	rot_key(tmp, kab + 0, 60);
	ft_memcpy(&ctx->k[10], tmp, 16);
	rot_key(tmp, klr + 0, 77);
	ft_memcpy(&ctx->ke[2], tmp, 16);
	rot_key(tmp, klr + 0, 94);
	ft_memcpy(&ctx->k[12], tmp, 16);
	ks_128_2(ctx, klr, kab);
}

static void		ks_192_256_2(t_camellia_ctx *ctx, uint8_t *klr, uint8_t *kab)
{
	uint8_t	tmp[16];

	rot_key(tmp, klr + 0, 77);
	ft_memcpy(&ctx->k[16], tmp, 16);
	rot_key(tmp, kab + 0, 77);
	ft_memcpy(&ctx->ke[4], tmp, 16);
	rot_key(tmp, klr + 16, 94);
	ft_memcpy(&ctx->k[18], tmp, 16);
	rot_key(tmp, kab + 0, 94);
	ft_memcpy(&ctx->k[20], tmp, 16);
	rot_key(tmp, klr + 0, 111);
	ft_memcpy(&ctx->k[22], tmp, 16);
	rot_key(tmp, kab + 16, 111);
	ft_memcpy(&ctx->kw[2], tmp, 16);
}

void			camellia_keyschedule_192_256(t_camellia_ctx *ctx, uint8_t *klr
		, uint8_t *kab)
{
	uint8_t	tmp[16];

	rot_key(tmp, klr, 0);
	ft_memcpy(&ctx->kw[0], tmp, 16);
	rot_key(tmp, kab + 16, 0);
	ft_memcpy(&ctx->k[0], tmp, 16);
	rot_key(tmp, klr + 16, 15);
	ft_memcpy(&ctx->k[2], tmp, 16);
	rot_key(tmp, kab + 0, 15);
	ft_memcpy(&ctx->k[4], tmp, 16);
	rot_key(tmp, klr + 16, 30);
	ft_memcpy(&ctx->ke[0], tmp, 16);
	rot_key(tmp, kab + 16, 30);
	ft_memcpy(&ctx->k[6], tmp, 16);
	rot_key(tmp, klr + 0, 45);
	ft_memcpy(&ctx->k[8], tmp, 16);
	rot_key(tmp, kab + 0, 45);
	ft_memcpy(&ctx->k[10], tmp, 16);
	rot_key(tmp, klr + 0, 60);
	ft_memcpy(&ctx->ke[2], tmp, 16);
	rot_key(tmp, klr + 16, 60);
	ft_memcpy(&ctx->k[12], tmp, 16);
	rot_key(tmp, kab + 16, 60);
	ft_memcpy(&ctx->k[14], tmp, 16);
	ks_192_256_2(ctx, klr, kab);
}
