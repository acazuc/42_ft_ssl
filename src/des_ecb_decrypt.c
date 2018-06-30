/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_decrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:36:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 19:15:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_ecb_decrypt_premod(t_des_ctx *ctx, uint64_t *data)
{
	(void)ctx;
	(void)data;
}

static void	des_ecb_decrypt_postmod(t_des_ctx *ctx, uint64_t *data)
{
	(void)ctx;
	(void)data;
}

int		des_ecb_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_decrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_ecb_decrypt_premod;
	ctx->post_mod = &des_ecb_decrypt_postmod;
	return (1);
}
