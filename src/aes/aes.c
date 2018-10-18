/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 12:44:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 18:49:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"
#include "libft.h"

static int	get_rounds_count(t_aes_ctx *ctx)
{
	if (ctx->key_len == 16)
		return (10);
	if (ctx->key_len == 24)
		return (12);
	return (14);
}

void		aes_encrypt(t_aes_ctx *ctx, uint8_t *block)
{
	uint8_t	rounds;
	uint8_t	i;

	ft_memxor(block, block, ctx->keys[0], 16);
	i = 1;
	rounds = get_rounds_count(ctx);
	while (i < rounds)
	{
		aes_subbytes(block);
		aes_shiftrows(block);
		aes_mixcolumns(block);
		ft_memxor(block, block, ctx->keys[i], 16);
		++i;
	}
	aes_subbytes(block);
	aes_shiftrows(block);
	ft_memxor(block, block, ctx->keys[rounds], 16);
}

void		aes_decrypt(t_aes_ctx *ctx, uint8_t *block)
{
	uint8_t	rounds;
	uint8_t	i;

	rounds = get_rounds_count(ctx);
	ft_memxor(block, block, ctx->keys[rounds], 16);
	i = 1;
	while (i < rounds)
	{
		aes_invshiftrows(block);
		aes_invsubbytes(block);
		ft_memxor(block, block, ctx->keys[rounds - i], 16);
		aes_invmixcolumns(block);
		++i;
	}
	aes_invshiftrows(block);
	aes_invsubbytes(block);
	ft_memxor(block, block, ctx->keys[0], 16);
}
