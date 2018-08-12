/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_mod_cbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 11:59:27 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "libft.h"

t_cipher_mod	g_cipher_mod_cbc = {cipher_cbc_premod, cipher_cbc_postmod, 0};

void	cipher_cbc_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
		ft_memcpy(ctx->mod2, data, ctx->cipher->block_size);
	else
		ft_memxor(data, data, ctx->mod1, ctx->cipher->block_size);
}

void	cipher_cbc_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
	{
		ft_memxor(data, data, ctx->mod1, ctx->cipher->block_size);
		ft_memcpy(ctx->mod1, ctx->mod2, ctx->cipher->block_size);
	}
	else
	{
		ft_memcpy(ctx->mod1, data, ctx->cipher->block_size);
	}
}
