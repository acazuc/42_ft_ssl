/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_ext_gcd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:48:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 16:44:01 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_ext_gcd_ctx *ctx, int ret)
{
	bignum_free(ctx->s);
	bignum_free(ctx->t);
	bignum_free(ctx->r);
	bignum_free(ctx->old_s);
	bignum_free(ctx->old_t);
	bignum_free(ctx->old_r);
	bignum_free(ctx->q);
	bignum_free(ctx->tmp1);
	bignum_free(ctx->tmp2);
	return (ret);
}

static int	do_init(t_ext_gcd_ctx *ctx)
{
	if (!(ctx->s = bignum_new()))
		return (0);
	if (!(ctx->t = bignum_new()))
		return (0);
	if (!bignum_one(ctx->t))
		return (0);
	if (!(ctx->r = bignum_dup(ctx->b)))
		return (0);
	if (!(ctx->old_s = bignum_new()))
		return (0);
	if (!bignum_one(ctx->old_s))
		return (0);
	if (!(ctx->old_t = bignum_new()))
		return (0);
	if (!(ctx->old_r = bignum_dup(ctx->a)))
		return (0);
	if (!(ctx->q = bignum_new()))
		return (0);
	if (!(ctx->tmp1 = bignum_new()))
		return (0);
	if (!(ctx->tmp2 = bignum_new()))
		return (0);
	return (1);
}

static int	do_part(t_ext_gcd_ctx *ctx, t_bignum *v, t_bignum *old_v)
{
	if (!bignum_mul(ctx->tmp1, ctx->q, v))
		return (0);
	if (!bignum_sub(ctx->tmp1, old_v, ctx->tmp1))
		return (0);
	if (!bignum_copy(old_v, v))
		return (0);
	if (!bignum_copy(v, ctx->tmp1))
		return (0);
	return (1);
}

int	bignum_ext_gcd(t_bignum *x, t_bignum *y, t_bignum *a, t_bignum *b)
{
	t_ext_gcd_ctx	ctx;

	bignum_trunc(a);
	bignum_trunc(b);
	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.x = x;
	ctx.y = y;
	ctx.a = a;
	ctx.b = b;
	if (!do_init(&ctx))
		return (do_clear(&ctx, 0));
	while (!bignum_is_zero(ctx.r))
	{
		if (!bignum_div(ctx.q, ctx.old_r, ctx.r))
			return (do_clear(&ctx, 0));
		if (!do_part(&ctx, ctx.r, ctx.old_r))
			return (do_clear(&ctx, 0));
		if (!do_part(&ctx, ctx.s, ctx.old_s))
			return (do_clear(&ctx, 0));
		if (!do_part(&ctx, ctx.t, ctx.old_t))
			return (do_clear(&ctx, 0));
	}
	if (!bignum_copy(x, ctx.old_t))
		return (do_clear(&ctx, 0));
	if (!bignum_copy(y, ctx.old_s))
		return (do_clear(&ctx, 0));
	bignum_trunc(x);
	bignum_trunc(y);
	return (do_clear(&ctx, 1));
}
