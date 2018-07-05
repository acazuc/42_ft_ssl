/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:21:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 15:53:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	cipher_init(t_cipher_ctx *ctx, uint32_t block_size)
{
	ctx->block_size = block_size;
	ctx->buff_pos = 0;
	ctx->ended = 0;
	if (!(ctx->iv = malloc(block_size)))
		return (0);
	if (!(ctx->mod1 = malloc(block_size)))
	{
		free(ctx->iv);
		return (0);
	}
	if (!(ctx->mod2 = malloc(block_size)))
	{
		free(ctx->mod1);
		free(ctx->iv);
		return (0);
	}
	if (!(ctx->buff = malloc(block_size)))
	{
		free(ctx->mod1);
		free(ctx->mod2);
		free(ctx->iv);
		return (0);
	}
	return (1);
}

void	cipher_free(t_cipher_ctx *ctx)
{
	free(ctx->buff);
	free(ctx->mod1);
	free(ctx->mod2);
	free(ctx->iv);
}
