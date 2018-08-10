/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ciper_mod_pcbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:53:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 21:53:15 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher.h"
#include "libft.h"

void	cipher_pcbc_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
	{
		ft_memcpy(ctx->mod2, data, ctx->block_size);
	}
	else
	{
		ft_memcpy(ctx->mod2, data, ctx->block_size);
		ft_memxor(data, data, ctx->mod1, ctx->block_size);
	}
}

void	cipher_pcbc_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
	{
		ft_memxor(data, data, ctx->mod1, ctx->block_size);
		ft_memxor(ctx->mod1, ctx->mod2, data, ctx->block_size);
	}
	else
	{
		ft_memxor(ctx->mod1, ctx->mod2, data, ctx->block_size);
	}
}
