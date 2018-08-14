/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod_inverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:48:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 17:40:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static int	do_clear(t_mod_inv_ctx *ctx, int ret)
{
	bignum_clear(&ctx->q);
	bignum_clear(&ctx->r);
	bignum_clear(&ctx->s);
	bignum_clear(&ctx->old_r);
	bignum_clear(&ctx->old_s);
	bignum_clear(&ctx->tmp);
	return (ret);
}

static int	do_init(t_mod_inv_ctx *ctx)
{
	bignum_init(&ctx->q);
	bignum_init(&ctx->r);
	bignum_init(&ctx->s);
	bignum_init(&ctx->old_r);
	bignum_init(&ctx->old_s);
	bignum_init(&ctx->tmp);
	if (!bignum_copy(&ctx->r, ctx->b))
		return (0);
	if (!bignum_copy(&ctx->old_r, ctx->a))
		return (0);
	if (!bignum_one(&ctx->old_s))
		return (0);
	return (1);
}

static int	do_part(t_mod_inv_ctx *ctx, t_bignum *v, t_bignum *old_v)
{
	if (!bignum_mul(&ctx->tmp, &ctx->q, v))
		return (0);
	if (!bignum_sub(&ctx->tmp, old_v, &ctx->tmp))
		return (0);
	if (!bignum_copy(old_v, v))
		return (0);
	if (!bignum_copy(v, &ctx->tmp))
		return (0);
	return (1);
}

int	bignum_mod_inverse(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_mod_inv_ctx	ctx;

	bignum_trunc(a);
	bignum_trunc(b);
	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.a = a;
	ctx.b = b;
	if (!do_init(&ctx))
		return (do_clear(&ctx, 0));
	while (!bignum_is_zero(&ctx.r))
	{
		if (!bignum_div(&ctx.q, &ctx.old_r, &ctx.r))
			return (do_clear(&ctx, 0));
		if (!do_part(&ctx, &ctx.r, &ctx.old_r))
			return (do_clear(&ctx, 0));
		if (!do_part(&ctx, &ctx.s, &ctx.old_s))
			return (do_clear(&ctx, 0));
	}
	if (ctx.old_s.sign && !bignum_add(&ctx.old_s, &ctx.old_s, &ctx.s))
		return (do_clear(&ctx, 0));
	bignum_trunc(&ctx.old_s);
	bignum_move(r, &ctx.old_s);
	return (do_clear(&ctx, 1));
}
