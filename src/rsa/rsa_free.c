/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:12:12 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:12:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void	rsa_free(t_rsa_ctx *ctx)
{
	free(ctx->n);
	free(ctx->e);
	free(ctx->q);
	free(ctx->p);
	free(ctx->d);
	free(ctx->dmp);
	free(ctx->dmq);
	free(ctx->coef);
}
