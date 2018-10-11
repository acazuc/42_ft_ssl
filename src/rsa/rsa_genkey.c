/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:16:40 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 14:44:54 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static int	do_clear(t_rsa_ctx *ctx)
{
	bignum_free(ctx->p);
	bignum_free(ctx->q);
	bignum_free(ctx->e);
	bignum_free(ctx->n);
	bignum_free(ctx->d);
	bignum_free(ctx->phi);
	bignum_free(ctx->dmp);
	bignum_free(ctx->dmq);
	bignum_free(ctx->coef);
	return (0);
}

int			rsa_genkey(t_rsa_ctx *ctx, uint32_t bits, uint32_t e, int print)
{
	if (bits < 16)
		return (0);
	ft_memset(ctx, 0, sizeof(*ctx));
	if (!(ctx->e = bignum_new()))
		return (do_clear(ctx));
	if (!bignum_grow(ctx->e, e))
		return (do_clear(ctx));
	if (!rsa_genkey_pq(ctx, bits, print))
		return (do_clear(ctx));
	if (!rsa_genkey_phi(ctx))
		return (do_clear(ctx));
	if (!(ctx->n = bignum_new()))
		return (do_clear(ctx));
	if (!bignum_mul(ctx->n, ctx->p, ctx->q))
		return (do_clear(ctx));
	if (!(ctx->d = bignum_new()))
		return (do_clear(ctx));
	if (!bignum_mod_inverse(ctx->d, ctx->e, ctx->phi))
		return (do_clear(ctx));
	if (!rsa_genkey_crt(ctx))
		return (do_clear(ctx));
	return (1);
}
