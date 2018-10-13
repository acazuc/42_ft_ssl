/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_crt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:49:06 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 11:11:57 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

static int	do_clear(t_bignum *tmp, t_bignum *one)
{
	bignum_clear(tmp);
	bignum_clear(one);
	return (0);
}

static int	do_dmp(t_rsa_ctx *ctx, t_bignum *tmp, t_bignum *one)
{
	if (!bignum_copy(tmp, ctx->p))
		return (0);
	if (!bignum_sub(tmp, tmp, one))
		return (0);
	if (!(ctx->dmp = bignum_new()))
		return (0);
	if (!bignum_mod(ctx->dmp, ctx->d, tmp))
		return (0);
	return (1);
}

static int	do_dmq(t_rsa_ctx *ctx, t_bignum *tmp, t_bignum *one)
{
	if (!bignum_copy(tmp, ctx->q))
		return (0);
	if (!bignum_sub(tmp, tmp, one))
		return (0);
	if (!(ctx->dmq = bignum_new()))
		return (0);
	if (!bignum_mod(ctx->dmq, ctx->d, tmp))
		return (0);
	return (1);
}

int			rsa_genkey_crt(t_rsa_ctx *ctx)
{
	t_bignum	tmp;
	t_bignum	one;

	bignum_init(&tmp);
	bignum_init(&one);
	if (!bignum_one(&one))
		return (do_clear(&tmp, &one));
	if (!do_dmp(ctx, &tmp, &one))
		return (do_clear(&tmp, &one));
	if (!do_dmq(ctx, &tmp, &one))
		return (do_clear(&tmp, &one));
	if (!(ctx->coef = bignum_new()))
		return (do_clear(&tmp, &one));
	if (!bignum_mod_inverse(ctx->coef, ctx->q, ctx->p))
		return (do_clear(&tmp, &one));
	do_clear(&tmp, &one);
	return (1);
}
