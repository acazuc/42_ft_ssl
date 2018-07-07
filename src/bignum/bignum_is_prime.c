/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_is_prime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:25:02 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 19:19:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	calc_n1_d_a_one(t_miller_ctx *ctx, t_bignum *bignum, t_bignum **one)
{
	ctx->a = NULL;
	ctx->n1 = NULL;
	ctx->d = NULL;
	*one = NULL;
	if (!(*one = bignum_new()))
		return (-1);
	if (!bignum_one(*one))
		return (-1);
	if (!(ctx->a = bignum_new()))
		return (-1);
	if (!(ctx->n1 = bignum_new()))
		return (-1);
	if (!(bignum_sub(ctx->n1, bignum, *one)))
		return (-1);
	if (!(ctx->d = bignum_dup(ctx->n1)))
		return (-1);
	ctx->s = 0;
	while (!bignum_is_odd(ctx->d))
	{
		if (!bignum_rshift1(ctx->d, ctx->d))
			return (0);
		++ctx->s;
	}
	return (1);
}

static int	calc_a(t_miller_ctx *ctx, t_bignum *one)
{
	if (!bignum_rand_range(ctx->a, ctx->n1))
		return (-1);
	if (!(bignum_add(ctx->a, ctx->a, one)))
		return (-1);
	return (1);
}

static int	do_clear(t_miller_ctx *ctx, t_bignum *one, int ret)
{
	bignum_free(ctx->n1);
	bignum_free(ctx->a);
	bignum_free(ctx->d);
	bignum_free(one);
	return (ret);
}

int	bignum_is_prime(t_bignum *bignum, int n)
{
	t_miller_ctx	ctx;
	t_bignum	*one;
	int		ret;
	int		i;

	if (bignum_is_zero(bignum) || bignum_is_one(bignum))
		return (0);
	if (!bignum_is_odd(bignum))
		return (bignum_is_word(bignum, 2));
	if (bignum_is_word(bignum, 3))
		return (1);
	if (n == BIGNUM_PRIME_CHECKS_AUTO)
		n = bignum_prime_checks_count(bignum);
	ret = calc_n1_d_a_one(&ctx, bignum, &one);
	if (ret <= 0)
		return (do_clear(&ctx, one, ret));
	i = 0;
	while (i < n)
	{
		ret = calc_a(&ctx, one);
		if (ret <= 0)
			return (do_clear(&ctx, one, ret));
		ret = bignum_is_prime_witness(&ctx, bignum);
		if (ret == -1)
			return (do_clear(&ctx, one, -1));
		if (ret)
			return (do_clear(&ctx, one, 0));
		++i;
	}
	return (do_clear(&ctx, one, 1));
}
