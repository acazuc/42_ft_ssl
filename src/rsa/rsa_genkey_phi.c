/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_phi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 15:14:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 15:50:12 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static int	do_clear(t_rsa_ctx *ctx, t_bignum *tmp, t_bignum *one)
{
	bignum_free(ctx->phi);
	bignum_free(tmp);
	bignum_free(one);
	return (0);
}

int		rsa_genkey_phi(t_rsa_ctx *ctx)
{
	t_bignum	*tmp;
	t_bignum	*one;

	ctx->phi = NULL;
	tmp = NULL;
	one = NULL;
	if (!(one = bignum_new()))
		return (do_clear(ctx, tmp, one));
	if (!bignum_one(one))
		return (do_clear(ctx, tmp, one));
	if (!(tmp = bignum_new()))
		return (do_clear(ctx, tmp, one));
	if (!bignum_sub(tmp, ctx->p, one))
		return (do_clear(ctx, tmp, one));
	if (!(ctx->phi = bignum_new()))
		return (do_clear(ctx, tmp, one));
	if (!bignum_sub(ctx->phi, ctx->q, one))
		return (do_clear(ctx, tmp, one));
	if (!bignum_mul(ctx->phi, ctx->phi, tmp))
		return (do_clear(ctx, tmp, one));
	bignum_free(tmp);
	bignum_free(one);
	return (1);
}
