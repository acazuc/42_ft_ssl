/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ofb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 19:09:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 11:49:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_ofb_premod(t_des_data *ctx, uint64_t *data)
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

void	des_ofb_postmod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
	{
		ctx->ctx[0].mode = !ctx->ctx[0].mode;
		ctx->ctx[1].mode = !ctx->ctx[1].mode;
		ctx->ctx[2].mode = !ctx->ctx[2].mode;
		ctx->tmp1 = *data;
		*data ^= ctx->tmp2;
	}
	else
	{
		ctx->tmp1 = *data;
		*data ^= ctx->tmp2;
	}
	*data = ft_swap_ulong(*data);
}
