/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:47:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:25:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "libft.h"

t_cipher	g_cipher_des2 = {(t_cipher_init)&des2_init
		, (t_cipher_update)&des2_update, (t_cipher_final)&des2_final
		, 8, 16, sizeof(t_des2_ctx)};

int	des2_init(t_des2_ctx *ctx, uint8_t *key)
{
	des_generate_keys(&ctx->ctx1, ft_swap_ulong(*(uint64_t*)key));
	des_generate_keys(&ctx->ctx2, ft_swap_ulong(*(uint64_t*)(key + 8)));
	return (1);
}

int	des2_update(t_des2_ctx *ctx, uint8_t *block, int mode)
{
	des_operate_block(&ctx->ctx1, (uint64_t*)block, mode);
	des_operate_block(&ctx->ctx2, (uint64_t*)block, !mode);
	des_operate_block(&ctx->ctx1, (uint64_t*)block, mode);
	return (1);
}

int	des2_final(t_des2_ctx *ctx)
{
	(void)ctx;
	return (1);
}
