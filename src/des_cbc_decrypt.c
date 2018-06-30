/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_decrypt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 19:45:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 19:16:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static void	des_cbc_decrypt_premod(t_des_ctx *ctx, uint64_t *data)
{
	ctx->tmp2 = *data;
}

static void	des_cbc_decrypt_postmod(t_des_ctx *ctx, uint64_t *data)
{
	*data ^= ctx->tmp1;
	ctx->tmp1 = ctx->tmp2;
}

int		des_cbc_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	if (!des_decrypt_init(ctx, key))
		return (0);
	ctx->pre_mod = &des_cbc_decrypt_premod;
	ctx->post_mod = &des_cbc_decrypt_postmod;
	ctx->tmp1 = ctx->iv;
	return (1);
}
