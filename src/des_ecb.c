/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/03 22:04:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	des_ecb_premod(t_des_ctx *ctx, uint64_t *data)
{
	(void)ctx;
	(void)data;
}

static void	des_ecb_postmod(t_des_ctx *ctx, uint64_t *data)
{
	(void)ctx;
	(void)data;
}

int		des_ecb_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_encrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_ecb_premod;
	ctx->post_mod = &des_ecb_postmod;
	return (1);
}

int		des_ecb_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_decrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_ecb_premod;
	ctx->post_mod = &des_ecb_postmod;
	return (1);
}
