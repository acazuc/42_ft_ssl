/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes128.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:13:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:31:17 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"

t_cipher	g_cipher_aes128 = {(t_cipher_init)&aes128_init
		, (t_cipher_update)&aes128_update, (t_cipher_final)&aes128_final
		, 16, 16, sizeof(t_aes128_ctx)};

int	aes128_init(t_aes128_ctx *ctx, uint8_t *key)
{
	aes_keyexpand(&ctx->ctx, key, 16);
	ctx->ctx.key_len = 16;
	return (1);
}

int	aes128_update(t_aes128_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aes_decrypt(&ctx->ctx, block);
	else
		aes_encrypt(&ctx->ctx, block);
	return (1);
}

int	aes128_final(t_aes128_ctx *ctx)
{
	(void)ctx;
	return (1);
}
