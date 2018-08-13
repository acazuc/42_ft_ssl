/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:13:16 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 19:11:56 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/rc4.h"

t_cipher	g_cipher_rc4 = {"RC4"
		, (t_cipher_init)&rc4_init
		, (t_cipher_update)&rc4_update
		, (t_cipher_final)&rc4_final
		, &g_cipher_mod_ecb_nopad, 1, 16, sizeof(t_rc4_ctx)};

int	rc4_init(t_rc4_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	rc4_init_state(ctx, key);
	return (1);
}

int	rc4_update(t_rc4_ctx *ctx, uint8_t *block, int mode)
{
	(void)mode;
	rc4_operate_block(ctx, block);
	return (1);
}

int	rc4_final(t_rc4_ctx *ctx)
{
	(void)ctx;
	return (1);
}
