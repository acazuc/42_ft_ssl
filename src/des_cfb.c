/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cfb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:53:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 12:49:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

void	des_cfb_premod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
	{
		ctx->tmp2 = *data;
		*data = ctx->tmp1;
		ctx->ctx[0].mode = !ctx->ctx[0].mode;
		ctx->ctx[1].mode = !ctx->ctx[1].mode;
		ctx->ctx[2].mode = !ctx->ctx[2].mode;
	}
	else
	{
		ctx->tmp2 = *data;
		*data = ctx->tmp1;
	}
	*data = ft_swap_ulong(*data);
}

void	des_cfb_postmod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
	{
		ctx->ctx[0].mode = !ctx->ctx[0].mode;
		ctx->ctx[1].mode = !ctx->ctx[1].mode;
		ctx->ctx[2].mode = !ctx->ctx[2].mode;
		*data ^= ctx->tmp2;
		ctx->tmp1 = ctx->tmp2;
	}
	else
	{
		*data ^= ctx->tmp2;
		ctx->tmp1 = *data;
	}
	*data = ft_swap_ulong(*data);
}
