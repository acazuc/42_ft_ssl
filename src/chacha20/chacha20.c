/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chacha20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 11:08:55 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 15:13:49 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/chacha20.h"
#include "ft_ssl.h"

void		chacha20_init_state(t_chacha20_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	ctx->state[0x0] = 0x61707865u;
	ctx->state[0x1] = 0x3320646Eu;
	ctx->state[0x2] = 0x79622D32u;
	ctx->state[0x3] = 0x6B206574u;
	ctx->state[0x4] = ((uint32_t*)key)[0];
	ctx->state[0x5] = ((uint32_t*)key)[1];
	ctx->state[0x6] = ((uint32_t*)key)[2];
	ctx->state[0x7] = ((uint32_t*)key)[3];
	ctx->state[0x8] = ((uint32_t*)key)[4];
	ctx->state[0x9] = ((uint32_t*)key)[5];
	ctx->state[0xA] = ((uint32_t*)key)[6];
	ctx->state[0xB] = ((uint32_t*)key)[7];
	ctx->state[0xC] = ((uint32_t*)iv)[0];
	ctx->state[0xD] = ((uint32_t*)iv)[1];
	ctx->state[0xE] = ((uint32_t*)iv)[2];
	ctx->state[0xF] = ((uint32_t*)iv)[3];
}

static void	chacha20_round(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	*a += *b;
	*d = rotate_left32(*d ^ *a, 16);
	*c += *d;
	*b = rotate_left32(*b ^ *c, 12);
	*a += *b;
	*d = rotate_left32(*d ^ *a, 8);
	*c += *d;
	*b = rotate_left32(*b ^ *c, 7);
}

static void	chacha20_rounds(uint32_t *x)
{
	chacha20_round(x + 0x0, x + 0x4, x + 0x8, x + 0xC);
	chacha20_round(x + 0x1, x + 0x5, x + 0x9, x + 0xD);
	chacha20_round(x + 0x2, x + 0x6, x + 0xA, x + 0xE);
	chacha20_round(x + 0x3, x + 0x7, x + 0xB, x + 0xF);
	chacha20_round(x + 0x0, x + 0x5, x + 0xA, x + 0xF);
	chacha20_round(x + 0x1, x + 0x6, x + 0xB, x + 0xC);
	chacha20_round(x + 0x2, x + 0x7, x + 0x8, x + 0xD);
	chacha20_round(x + 0x3, x + 0x4, x + 0x9, x + 0xE);
}

void		chacha20_operate_block(t_chacha20_ctx *ctx, uint8_t *block)
{
	uint32_t	tmp[16];
	uint32_t	x[16];
	int			i;

	ft_memcpy(tmp, block, 16 * 4);
	ft_memcpy(x, ctx->state, 16 * 4);
	i = 0;
	while (i < 10)
	{
		chacha20_rounds(x);
		++i;
	}
	i = 0;
	while (i < 16)
	{
		((uint32_t*)block)[i] ^= x[i] + ctx->state[i];
		++i;
	}
	ctx->state[12]++;
	if (!ctx->state[12])
		ctx->state[13]++;
}
