/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ciper_mod_pcbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:53:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/17 19:57:01 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "libft.h"

t_cipher_mod	g_cipher_mod_pcbc = {cipher_pcbc_premod,
	cipher_pcbc_postmod, 0, 1};

void	cipher_pcbc_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	ft_memcpy(ctx->mod2, data, ctx->cipher->block_size);
	if (!ctx->mode)
		ft_memxor(data, data, ctx->mod1, ctx->cipher->block_size);
}

void	cipher_pcbc_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
		ft_memxor(data, data, ctx->mod1, ctx->cipher->block_size);
	ft_memxor(ctx->mod1, ctx->mod2, data, ctx->cipher->block_size);
}
