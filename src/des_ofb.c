/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ofb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 19:09:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/03 22:02:13 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_ofb_premod(t_des_ctx *ctx, uint64_t *data)
{
	if (ctx->mode)
	{
		ctx->tmp2 = *data;
		*data = ctx->tmp1;
		ctx->mode = 0;
		ctx->tmp1 = 1;
	}
	else
	{
		ctx->tmp2 = *data;
		*data = ctx->tmp1;
		ctx->tmp1 = 0;
	}
}

static void	des_ofb_postmod(t_des_ctx *ctx, uint64_t *data)
{
	if (ctx->tmp1)
	{
		ctx->mode = 1;
		ctx->tmp1 = *data;
		*data ^= ctx->tmp2;
	}
	else
	{
		ctx->tmp1 = *data;
		*data ^= ctx->tmp2;
	}
}

int		des_ofb_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_encrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_ofb_premod;
	ctx->post_mod = &des_ofb_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}

int		des_ofb_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_decrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_ofb_premod;
	ctx->post_mod = &des_ofb_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}
