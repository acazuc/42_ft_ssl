/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chacha20.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 11:08:55 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:01:33 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/chacha20.h"
#include "ft_ssl.h"

void		chacha20_init_state(t_chacha20_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	ctx->state[0] = ((uint32_t)'e') | ((uint32_t)'x' << 8)
		| ((uint32_t)'p' << 16) | ((uint32_t)'a' << 24);
	ctx->state[1] = ((uint32_t)'n') | ((uint32_t)'d' << 8)
		| ((uint32_t)' ' << 16) | ((uint32_t)'3' << 24);
	ctx->state[2] = ((uint32_t)'2') | ((uint32_t)'-' << 8)
		| ((uint32_t)'b' << 16) | ((uint32_t)'y' << 24);
	ctx->state[3] = ((uint32_t)'t') | ((uint32_t)'e' << 8)
		| ((uint32_t)' ' << 16) | ((uint32_t)'k' << 24);
	ctx->state[4] = *(uint32_t*)key;
	ctx->state[5] = *(uint32_t*)(key + 4);
	ctx->state[6] = *(uint32_t*)(key + 8);
	ctx->state[7] = *(uint32_t*)(key + 12);
	ctx->state[8] = *(uint32_t*)(key + 16);
	ctx->state[9] = *(uint32_t*)(key + 20);
	ctx->state[10] = *(uint32_t*)(key + 24);
	ctx->state[11] = *(uint32_t*)(key + 28);
	ctx->state[12] = *(uint32_t*)iv;
	ctx->state[13] = *(uint32_t*)(iv + 4);
	ctx->state[14] = *(uint32_t*)(iv + 8);
	ctx->state[15] = *(uint32_t*)(iv + 12);
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
		chacha20_round(&x[0], &x[4], &x[8], &x[12]);
		chacha20_round(&x[1], &x[5], &x[9], &x[13]);
		chacha20_round(&x[2], &x[6], &x[10], &x[14]);
		chacha20_round(&x[3], &x[7], &x[11], &x[15]);
		chacha20_round(&x[0], &x[5], &x[10], &x[15]);
		chacha20_round(&x[1], &x[6], &x[11], &x[12]);
		chacha20_round(&x[2], &x[7], &x[8], &x[13]);
		chacha20_round(&x[3], &x[4], &x[9], &x[14]);
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
