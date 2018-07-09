/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:16:40 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 18:18:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int		rsa_genkey(t_rsa_ctx *ctx, uint64_t bits, int print)
{
	if (bits < 16)
		return (0);
	if (!rsa_genkey_pq(ctx, bits, print))
		return (0);
	if (!rsa_genkey_phi(ctx))
	{
		bignum_free(ctx->p);
		bignum_free(ctx->q);
		return (0);
	}
	if (!(ctx->e = bignum_new()))
	{
		bignum_free(ctx->p);
		bignum_free(ctx->q);
		return (0);
	}
	if (!bignum_grow(ctx->e, 65537))
	{
		bignum_free(ctx->e);
		bignum_free(ctx->p);
		bignum_free(ctx->q);
		return (0);
	}
	if (!(ctx->n = bignum_new()))
	{
		bignum_free(ctx->e);
		bignum_free(ctx->q);
		bignum_free(ctx->p);
		return (0);
	}
	if (!bignum_mul(ctx->n, ctx->p, ctx->q))
	{
		bignum_free(ctx->e);
		bignum_free(ctx->p);
		bignum_free(ctx->q);
		bignum_free(ctx->n);
		return (0);
	}
	if (!(ctx->d = bignum_new()))
	{
		bignum_free(ctx->e);
		bignum_free(ctx->p);
		bignum_free(ctx->q);
		bignum_free(ctx->n);
		return (0);
	}
	if (!bignum_mod_inverse(ctx->d, ctx->e, ctx->phi))
		return (0);
	return (1);
}
