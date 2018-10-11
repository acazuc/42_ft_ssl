/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_rsa_priv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:40:08 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 11:11:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

static int	do_clear(t_vecu8 *vec)
{
	vecu8_free(vec);
	return (-1);
}

static int	write_bignums(t_vecu8 *vec, t_rsa_ctx *ctx)
{
	if (!pem_bignum_write(vec, ctx->n))
		return (0);
	if (!pem_bignum_write(vec, ctx->e))
		return (0);
	if (!pem_bignum_write(vec, ctx->d))
		return (0);
	if (!pem_bignum_write(vec, ctx->p))
		return (0);
	if (!pem_bignum_write(vec, ctx->q))
		return (0);
	if (!pem_bignum_write(vec, ctx->dmp))
		return (0);
	if (!pem_bignum_write(vec, ctx->dmq))
		return (0);
	if (!pem_bignum_write(vec, ctx->coef))
		return (0);
	return (1);
}

static int	get_len(t_rsa_ctx *ctx)
{
	int	total;

	total = 3;
	total += pem_len_len(pem_bignum_len(ctx->n));
	total += pem_bignum_len(ctx->n) + 1;
	total += pem_len_len(pem_bignum_len(ctx->e));
	total += pem_bignum_len(ctx->e) + 1;
	total += pem_len_len(pem_bignum_len(ctx->d));
	total += pem_bignum_len(ctx->d) + 1;
	total += pem_len_len(pem_bignum_len(ctx->p));
	total += pem_bignum_len(ctx->p) + 1;
	total += pem_len_len(pem_bignum_len(ctx->q));
	total += pem_bignum_len(ctx->q) + 1;
	total += pem_len_len(pem_bignum_len(ctx->dmp));
	total += pem_bignum_len(ctx->dmp) + 1;
	total += pem_len_len(pem_bignum_len(ctx->dmq));
	total += pem_bignum_len(ctx->dmq) + 1;
	total += pem_len_len(pem_bignum_len(ctx->coef));
	total += pem_bignum_len(ctx->coef) + 1;
	return (total);
}

int			pem_write_rsa_priv(char **dst, t_rsa_ctx *ctx)
{
	t_vecu8	vec;
	uint8_t	tmp[64];

	vecu8_init(&vec);
	if (!vecu8_pushu8(&vec, 0x30))
		return (do_clear(&vec));
	if (!vecu8_push(&vec, tmp, pem_write_len(tmp, get_len(ctx))))
		return (do_clear(&vec));
	if (!vecu8_push(&vec, (uint8_t*)"\x2\x1\x0", 3))
		return (do_clear(&vec));
	if (!write_bignums(&vec, ctx))
		return (do_clear(&vec));
	*dst = (char*)vec.data;
	return (vec.size);
}
