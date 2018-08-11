/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:43:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:25:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "libft.h"

t_cipher	g_cipher_des1 = {(t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update, (t_cipher_final)&des1_final
		, 8, 8, sizeof(t_des1_ctx)};

int	des1_init(t_des1_ctx *ctx, uint8_t *key)
{
	des_generate_keys(&ctx->ctx1, ft_swap_ulong(*(uint64_t*)key));
	return (1);
}

int	des1_update(t_des1_ctx *ctx, uint8_t *block, int mode)
{
	des_operate_block(&ctx->ctx1, (uint64_t*)block, mode);
	return (1);
}

int	des1_final(t_des1_ctx *ctx)
{
	(void)ctx;
	return (1);
}
