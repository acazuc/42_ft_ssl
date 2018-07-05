/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_mod_ofb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 19:09:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 15:04:48 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	cipher_ofb_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
	{
		ft_memcpy(ctx->mod2, data, ctx->block_size);
		ft_memcpy(data, ctx->mod1, ctx->block_size);
		ctx->mode = 0;
		ctx->mod3 = 1;
	}
	else
	{
		ft_memcpy(ctx->mod2, data, ctx->block_size);
		ft_memcpy(data, ctx->mod1, ctx->block_size);
		ctx->mod3 = 0;
	}
}

void	cipher_ofb_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mod1)
	{
		ctx->mode = 1;
		ft_memcpy(ctx->mod1, data, ctx->block_size);
		ft_memxor(data, data, ctx->mod2, ctx->block_size);
	}
	else
	{
		ft_memcpy(ctx->mod1, data, ctx->block_size);
		ft_memxor(data, data, ctx->mod2, ctx->block_size);
	}
}
