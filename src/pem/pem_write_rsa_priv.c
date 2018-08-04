/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_rsa_priv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 19:40:08 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 17:35:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

static int	write_bignums(t_vecu8 *vec, t_rsa_ctx *ctx)
{
	if (!pem_write_bignum(vec, ctx->n))
		return (0);
	if (!pem_write_bignum(vec, ctx->e))
		return (0);
	if (!pem_write_bignum(vec, ctx->d))
		return (0);
	if (!pem_write_bignum(vec, ctx->p))
		return (0);
	if (!pem_write_bignum(vec, ctx->q))
		return (0);
	if (!pem_write_bignum(vec, ctx->dmp))
		return (0);
	if (!pem_write_bignum(vec, ctx->dmq))
		return (0);
	if (!pem_write_bignum(vec, ctx->coef))
		return (0);
	return (1);
}

static int	get_len(t_rsa_ctx *ctx)
{
	int	total;
	uint8_t	osef[90];

	total = 3;
	total += pem_write_len(osef, ctx->n->len * sizeof(*ctx->n->data));
	total += ctx->n->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->e->len * sizeof(*ctx->n->data));
	total += ctx->e->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->d->len * sizeof(*ctx->n->data));
	total += ctx->d->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->p->len * sizeof(*ctx->n->data));
	total += ctx->p->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->q->len * sizeof(*ctx->n->data));
	total += ctx->q->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->dmp->len * sizeof(*ctx->n->data));
	total += ctx->dmp->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->dmq->len * sizeof(*ctx->n->data));
	total += ctx->dmq->len * sizeof(*ctx->n->data) + 2;
	total += pem_write_len(osef, ctx->coef->len * sizeof(*ctx->n->data));
	total += ctx->coef->len * sizeof(*ctx->n->data) + 2;
	return (total);
}

int	pem_write_rsa_priv(char **dst, t_rsa_ctx *ctx)
{
	t_vecu8	vec;
	uint8_t	tmp[64];

	vecu8_init(&vec);
	if (!vecu8_pushu8(&vec, 0x30))
		return (-1);
	if (!vecu8_push(&vec, tmp, pem_write_len(tmp, get_len(ctx))))
		return (-1);
	if (!vecu8_pushu8(&vec, 0x2))
		return (-1);
	if (!vecu8_pushu8(&vec, 0x1))
		return (-1);
	if (!vecu8_pushu8(&vec, 0))
		return (-1);
	if (!write_bignums(&vec, ctx))
		return (-1);
	*dst = vec.data;
	vec.data = NULL;
	return (vec.size);
}
