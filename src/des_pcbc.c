/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pcbc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:53:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 11:38:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_pcbc_premod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
	{
		ctx->tmp2 = *data;
	}
	else
	{
		ctx->tmp2 = *data;
		*data ^= ctx->tmp1;
	}
	*data = ft_swap_ulong(*data);
}

void	des_pcbc_postmod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
	{
		*data ^= ctx->tmp1;
		ctx->tmp1 = ctx->tmp2 ^ *data;
	}
	else
	{
		ctx->tmp1 = ctx->tmp2 ^ *data;
	}
	*data = ft_swap_ulong(*data);
}
