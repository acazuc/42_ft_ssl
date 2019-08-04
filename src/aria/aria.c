/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aria.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:33:09 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:57:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"
#include "libft.h"

static int	get_rounds_count(t_aria_ctx *ctx)
{
	if (ctx->key_len == 16)
		return (11);
	if (ctx->key_len == 24)
		return (13);
	return (15);
}

void		aria_encrypt(t_aria_ctx *ctx, uint8_t *block)
{
	uint8_t	rounds;
	uint8_t	i;

	rounds = get_rounds_count(ctx);
	i = 0;
	while (i < rounds)
	{
		if (i & 1)
			aria_fe(block, block, ctx->ekeys[i]);
		else
			aria_fo(block, block, ctx->ekeys[i]);
		++i;
	}
	ft_memxor(block, block, ctx->ekeys[i++], 16);
	aria_sl2(block, block);
	ft_memxor(block, block, ctx->ekeys[i++], 16);
}

void		aria_decrypt(t_aria_ctx *ctx, uint8_t *block)
{
	uint8_t	rounds;
	uint8_t	i;

	rounds = get_rounds_count(ctx);
	i = 0;
	while (i < rounds)
	{
		if (i & 1)
			aria_fe(block, block, ctx->dkeys[i]);
		else
			aria_fo(block, block, ctx->dkeys[i]);
		++i;
	}
	ft_memxor(block, block, ctx->dkeys[i++], 16);
	aria_sl2(block, block);
	ft_memxor(block, block, ctx->dkeys[i++], 16);
}
