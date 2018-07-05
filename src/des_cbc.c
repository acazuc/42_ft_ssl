/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 12:11:02 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_cbc_premod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
		ctx->tmp2 = *data;
	else
		*data ^= ctx->tmp1;
	*data = ft_swap_ulong(*data);
}

void	des_cbc_postmod(t_des_data *ctx, uint64_t *data)
{
	*data = ft_swap_ulong(*data);
	if (ctx->mode)
	{
		*data ^= ctx->tmp1;
		ctx->tmp1 = ctx->tmp2;
	}
	else
	{
		ctx->tmp1 = *data;
	}
	*data = ft_swap_ulong(*data);
}
