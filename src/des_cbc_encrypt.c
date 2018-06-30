/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_encrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 19:16:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_cbc_encrypt_premod(t_des_ctx *ctx, uint64_t *data)
{
	*data ^= ctx->tmp1;
}

static void	des_cbc_encrypt_postmod(t_des_ctx *ctx, uint64_t *data)
{
	ctx->tmp1 = *data;
}

int		des_cbc_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_encrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_cbc_encrypt_premod;
	ctx->post_mod = &des_cbc_encrypt_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}
