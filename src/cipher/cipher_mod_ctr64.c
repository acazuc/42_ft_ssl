/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_mod_ctr64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 21:49:27 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/17 19:56:15 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "libft.h"

t_cipher_mod	g_cipher_mod_ctr64 = {cipher_ctr64_premod
	, cipher_ctr64_postmod, 1, 1};

void	cipher_ctr64_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	ft_memcpy(ctx->mod2, data, ctx->cipher->block_size);
	ft_memcpy(data, ctx->mod1, ctx->cipher->block_size);
	if (ctx->mode)
	{
		ctx->mode = 0;
		ctx->mod3 = 1;
	}
	else
		ctx->mod3 = 0;
}

void	cipher_ctr64_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mod3)
		ctx->mode = 1;
	ft_memcpy(ctx->mod1, data, ctx->cipher->block_size);
	*(uint32_t*)(ctx->mod1 + 4) = ft_swap_uint(ft_swap_uint(
				*(uint32_t*)(ctx->mod1 + 4)) + 1);
	ft_memxor(data, data, ctx->mod2, ctx->cipher->block_size);
}
