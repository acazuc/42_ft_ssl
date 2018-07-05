/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_mod_cbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 15:55:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	cipher_cbc_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
		ft_memcpy(ctx->mod2, data, ctx->block_size);
	else
		ft_memxor(data, data, ctx->mod1, ctx->block_size);
}

void	cipher_cbc_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	if (ctx->mode)
	{
		ft_memxor(data, data, ctx->mod1, ctx->block_size);
		ft_memcpy(ctx->mod1, ctx->mod2, ctx->block_size);
	}
	else
	{
		ft_memcpy(ctx->mod1, data, ctx->block_size);
	}
}
