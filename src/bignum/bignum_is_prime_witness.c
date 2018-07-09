/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_is_prime_witness.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:22:26 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 14:28:23 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_is_prime_witness(t_miller_ctx *ctx, t_bignum *bignum)
{
	if (!bignum_mod_exp(ctx->a, ctx->a, ctx->d, bignum))
		return (-1);
	if (bignum_is_one(ctx->a) || !bignum_cmp(ctx->a, ctx->n1))
		return (0);
	while (ctx->s > 1)
	{
		if (!bignum_mul(ctx->a, ctx->a, ctx->a))
			return (-1);
		if (!bignum_mod(ctx->a, ctx->a, bignum))
			return (-1);
		if (bignum_is_one(ctx->a))
			return (1);
		if (!bignum_cmp(ctx->a, ctx->n1))
			return (0);
		--ctx->s;
	}
	return (1);
}
