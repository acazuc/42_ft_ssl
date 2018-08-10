/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 14:37:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:24:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int	rsa_encrypt(t_rsa_ctx *ctx, t_bignum *c, t_bignum *m)
{
	if (m->sign || bignum_cmp(m, ctx->n) >= 0)
		return (0);
	return (bignum_mod_exp(c, m, ctx->e, ctx->n));
}

int	rsa_decrypt(t_rsa_ctx *ctx, t_bignum *m, t_bignum *c)
{
	t_bignum	m1;
	t_bignum	m2;

	if (c->sign || bignum_cmp(c, ctx->n) >= 0)
		return (0);
	bignum_init(&m1);
	bignum_init(&m2);
	if (!bignum_mod_exp(&m1, c, ctx->dmp, ctx->p)
			|| !bignum_mod_exp(&m2, c, ctx->dmq, ctx->q)
			|| !bignum_sub(&m1, &m1, &m2)
			|| !bignum_mul(&m1, &m1, ctx->coef)
			|| !bignum_mod(&m1, &m1, ctx->p)
			|| !bignum_mul(&m1, &m1, ctx->q)
			|| !bignum_add(&m1, &m1, &m2))
	{
		bignum_clear(&m1);
		bignum_clear(&m2);
		return (0);
	}
	bignum_clear(&m2);
	bignum_move(m, &m1);
	return (1);
	//return (bignum_mod_exp(m, c, ctx->d, ctx->n));
}

int	rsa_sign(t_rsa_ctx *ctx, t_bignum *s, t_bignum *m)
{
	if (m->sign || bignum_cmp(m, ctx->n) >= 0)
		return (0);
	return (bignum_mod_exp(s, m, ctx->d, ctx->n));
}

int	rsa_verify(t_rsa_ctx *ctx, t_bignum *m, t_bignum *s)
{
	if (s->sign || bignum_cmp(s, ctx->n) >= 0)
		return (0);
	return (bignum_mod_exp(m, s, ctx->e, ctx->n));
}
