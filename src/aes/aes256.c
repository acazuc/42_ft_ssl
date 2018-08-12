/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:15:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 11:56:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"

t_cipher	g_cipher_aes256 = {(t_cipher_init)&aes256_init
		, (t_cipher_update)&aes256_update, (t_cipher_final)&aes256_final
		, 16, 32, sizeof(t_aes256_ctx)};

int	aes256_init(t_aes256_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aes_keyexpand(&ctx->ctx, key, 32);
	ctx->ctx.key_len = 32;
	return (1);
}

int	aes256_update(t_aes256_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aes_decrypt(&ctx->ctx, block);
	else
		aes_encrypt(&ctx->ctx, block);
	return (1);
}

int	aes256_final(t_aes256_ctx *ctx)
{
	(void)ctx;
	return (1);
}
