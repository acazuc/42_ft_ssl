/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:08:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 12:59:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/rc4.h"

void		rc4_init_state(t_rc4_ctx *ctx, uint8_t *key)
{
	uint8_t	tmp;
	uint8_t	j;
	int		i;

	ctx->i = 0;
	ctx->j = 0;
	i = 0;
	while (i < 256)
	{
		ctx->state[i] = i;
		++i;
	}
	i = 0;
	j = 0;
	while (i < 256)
	{
		j += ctx->state[i] + key[i % 16];
		tmp = ctx->state[i];
		ctx->state[i] = ctx->state[j];
		ctx->state[j] = tmp;
		++i;
	}
}

void		rc4_operate_block(t_rc4_ctx *ctx, uint8_t *block)
{
	uint8_t	tmp;

	ctx->i++;
	ctx->j += ctx->state[ctx->i];
	tmp = ctx->state[ctx->i];
	ctx->state[ctx->i] = ctx->state[ctx->j];
	ctx->state[ctx->j] = tmp;
	tmp = ctx->state[ctx->i] + ctx->state[ctx->j];
	*block ^= ctx->state[tmp];
}
