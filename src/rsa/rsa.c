/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 14:37:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 20:31:09 by acazuc           ###   ########.fr       */
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
	if (c->sign || bignum_cmp(c, ctx->n) >= 0)
		return (0);
	return (bignum_mod_exp(m, c, ctx->d, ctx->n));
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
