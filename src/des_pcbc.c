/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pcbc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:53:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/03 21:57:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_pcbc_premod(t_des_ctx *ctx, uint64_t *data)
{
	if (ctx->mode)
	{
		ctx->tmp2 = *data;
	}
	else
	{
		ctx->tmp2 = *data;
		*data ^= ctx->tmp1;
	}
}

static void	des_pcbc_postmod(t_des_ctx *ctx, uint64_t *data)
{
	if (ctx->mode)
	{
		*data ^= ctx->tmp1;
		ctx->tmp1 = ctx->tmp2 ^ *data;
	}
	else
	{
		ctx->tmp1 = ctx->tmp2 ^ *data;
	}
}

int		des_pcbc_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_encrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_pcbc_premod;
	ctx->post_mod = &des_pcbc_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}

int		des_pcbc_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_decrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_pcbc_premod;
	ctx->post_mod = &des_pcbc_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}
