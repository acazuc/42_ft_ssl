/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 14:37:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 14:39:12 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int	rsa_enc(t_rsa_ctx *ctx, t_bignum *c, t_bignum *m)
{
	if (m->sign || bignum_cmp(m, ctx->n) >= 0)
		return (0);
	return (bignum_mod_exp(c, m, ctx->e, ctx->n));
}

int	rsa_dec(t_rsa_ctx *ctx, t_bignum *m, t_bignum *c)
{
	t_bignum	m1;
	t_bignum	m2;
	int			ret;

	if (c->sign || bignum_cmp(c, ctx->n) >= 0)
		return (0);
	bignum_init(&m1);
	bignum_init(&m2);
	ret = 1;
	if (!bignum_mod_exp(&m1, c, ctx->dmp, ctx->p)
			|| !bignum_mod_exp(&m2, c, ctx->dmq, ctx->q)
			|| !bignum_sub(&m1, &m1, &m2)
			|| !bignum_mul(&m1, &m1, ctx->coef)
			|| !bignum_mod(&m1, &m1, ctx->p)
			|| !bignum_mul(&m1, &m1, ctx->q)
			|| !bignum_add(&m1, &m1, &m2))
		ret = 0;
	bignum_clear(&m1);
	bignum_clear(&m2);
	return (ret);
}

int	rsa_sign(t_rsa_ctx *ctx, t_bignum *s, t_bignum *m)
{
	return (rsa_dec(ctx, s, m));
}

int	rsa_verify(t_rsa_ctx *ctx, t_bignum *m, t_bignum *s)
{
	return (rsa_enc(ctx, m, s));
}
