/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_mod_ofb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 19:09:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 15:15:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "libft.h"

t_cipher_mod	g_cipher_mod_ofb = {cipher_ofb_premod, cipher_ofb_postmod, 1};

void	cipher_ofb_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
	{
		ft_memcpy(ctx->mod2, data, ctx->cipher->block_size);
		ft_memcpy(data, ctx->mod1, ctx->cipher->block_size);
		ctx->mode = 0;
		ctx->mod3 = 1;
	}
	else
	{
		ft_memcpy(ctx->mod2, data, ctx->cipher->block_size);
		ft_memcpy(data, ctx->mod1, ctx->cipher->block_size);
		ctx->mod3 = 0;
	}
}

void	cipher_ofb_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mod3)
	{
		ctx->mode = 1;
		ft_memcpy(ctx->mod1, data, ctx->cipher->block_size);
		ft_memxor(data, data, ctx->mod2, ctx->cipher->block_size);
	}
	else
	{
		ft_memcpy(ctx->mod1, data, ctx->cipher->block_size);
		ft_memxor(data, data, ctx->mod2, ctx->cipher->block_size);
	}
}
