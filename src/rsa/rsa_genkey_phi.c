/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_phi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 15:14:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:26:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

static int	do_clear(t_rsa_ctx *ctx, t_bignum *tmp, t_bignum *one)
{
	bignum_free(ctx->phi);
	bignum_clear(tmp);
	bignum_clear(one);
	return (0);
}

int			rsa_genkey_phi(t_rsa_ctx *ctx)
{
	t_bignum	tmp;
	t_bignum	one;

	bignum_init(&tmp);
	bignum_init(&one);
	if (!bignum_one(&one))
		return (do_clear(ctx, &tmp, &one));
	if (!bignum_sub(&tmp, ctx->p, &one))
		return (do_clear(ctx, &tmp, &one));
	if (!(ctx->phi = bignum_new()))
		return (do_clear(ctx, &tmp, &one));
	if (!bignum_sub(ctx->phi, ctx->q, &one))
		return (do_clear(ctx, &tmp, &one));
	if (!bignum_mul(ctx->phi, ctx->phi, &tmp))
		return (do_clear(ctx, &tmp, &one));
	bignum_clear(&tmp);
	bignum_clear(&one);
	return (1);
}
