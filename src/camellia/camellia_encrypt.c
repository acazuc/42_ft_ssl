/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia_encrypt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:54:06 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 12:06:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "libft.h"

static void	do_loop(t_camellia_ctx *ctx, uint64_t *d1, uint64_t *d2, int i)
{
	if (i)
	{
		*d1 = camellia_fl(*d1, ctx->ke[(i - 1) * 2 + 0]);
		*d2 = camellia_flinv(*d2, ctx->ke[(i - 1) * 2 + 1]);
	}
	*d2 ^= camellia_f(*d1, ctx->k[i * 6 + 0]);
	*d1 ^= camellia_f(*d2, ctx->k[i * 6 + 1]);
	*d2 ^= camellia_f(*d1, ctx->k[i * 6 + 2]);
	*d1 ^= camellia_f(*d2, ctx->k[i * 6 + 3]);
	*d2 ^= camellia_f(*d1, ctx->k[i * 6 + 4]);
	*d1 ^= camellia_f(*d2, ctx->k[i * 6 + 5]);
}

void		camellia_encrypt(t_camellia_ctx *ctx, uint8_t *block)
{
	uint64_t	d1;
	uint64_t	d2;

	d1 = ft_swap_long(*(uint64_t*)block);
	d2 = ft_swap_long(*(uint64_t*)(block + 8));
	d1 ^= ctx->kw[0];
	d2 ^= ctx->kw[1];
	do_loop(ctx, &d1, &d2, 0);
	do_loop(ctx, &d1, &d2, 1);
	do_loop(ctx, &d1, &d2, 2);
	if (ctx->key_len != 16)
		do_loop(ctx, &d1, &d2, 3);
	d2 ^= ctx->kw[2];
	d1 ^= ctx->kw[3];
	*(uint64_t*)block = ft_swap_long(d2);
	*(uint64_t*)(block + 8) = ft_swap_long(d1);
}
