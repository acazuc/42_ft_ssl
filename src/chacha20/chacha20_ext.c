/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chacha20_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 10:59:32 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:00:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/chacha20.h"

t_cipher	g_cipher_chacha20 = {"CHACHA20",
	(t_cipher_init)chacha20_init,
	(t_cipher_update)chacha20_update,
	(t_cipher_final)chacha20_final,
	&g_cipher_mod_ecb_nopad, 64, 32, sizeof(t_chacha20_ctx)};

int	chacha20_init(t_chacha20_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	chacha20_init_state(ctx, key, iv);
	return (1);
}

int	chacha20_update(t_chacha20_ctx *ctx, uint8_t *block, int mode)
{
	(void)mode;
	chacha20_operate_block(ctx, block);
	return (1);
}

int	chacha20_final(t_chacha20_ctx *ctx)
{
	(void)ctx;
	return (1);
}
