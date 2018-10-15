/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:12:12 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 14:39:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void	rsa_free(t_rsa_ctx *ctx)
{
	bignum_free(ctx->n);
	bignum_free(ctx->e);
	bignum_free(ctx->q);
	bignum_free(ctx->p);
	bignum_free(ctx->d);
	bignum_free(ctx->phi);
	bignum_free(ctx->dmp);
	bignum_free(ctx->dmq);
	bignum_free(ctx->coef);
}
