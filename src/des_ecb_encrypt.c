/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 19:15:55 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_ecb_encrypt_premod(t_des_ctx *ctx, uint64_t *data)
{
	(void)ctx;
	(void)data;
}

static void	des_ecb_encrypt_postmod(t_des_ctx *ctx, uint64_t *data)
{
	(void)ctx;
	(void)data;
}

int		des_ecb_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_encrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_ecb_encrypt_premod;
	ctx->post_mod = &des_ecb_encrypt_postmod;
	return (1);
}
