/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cfb_decrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:52:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 19:15:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_cfb_decrypt_premod(t_des_ctx *ctx, uint64_t *data)
{
	ctx->tmp2 = *data;
	*data = ctx->tmp1;
	ctx->mode = 0;
}

static void	des_cfb_decrypt_postmod(t_des_ctx *ctx, uint64_t *data)
{
	ctx->mode = 1;
	*data ^= ctx->tmp2;
	ctx->tmp1 = ctx->tmp2;
}

int		des_cfb_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_decrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_cfb_decrypt_premod;
	ctx->post_mod = &des_cfb_decrypt_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}
