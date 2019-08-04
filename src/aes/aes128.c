/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes128.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:13:48 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:05:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"

t_cipher	g_cipher_aes128_ecb = {"AES-128-ECB",
	(t_cipher_init)aes128_init,
	(t_cipher_update)aes128_update,
	(t_cipher_final)aes128_final,
	&g_cipher_mod_ecb, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_cbc = {"AES-128-CBC",
	(t_cipher_init)aes128_init,
	(t_cipher_update)aes128_update,
	(t_cipher_final)aes128_final,
	&g_cipher_mod_cbc, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_pcbc = {"AES-128-PCBC",
	(t_cipher_init)aes128_init,
	(t_cipher_update)aes128_update,
	(t_cipher_final)aes128_final,
	&g_cipher_mod_pcbc, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_cfb = {"AES-128-CFB",
	(t_cipher_init)aes128_init,
	(t_cipher_update)aes128_update,
	(t_cipher_final)aes128_final,
	&g_cipher_mod_cfb, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_ofb = {"AES-128-OFB",
	(t_cipher_init)aes128_init,
	(t_cipher_update)aes128_update,
	(t_cipher_final)aes128_final,
	&g_cipher_mod_ofb, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_ctr = {"AES-128-CTR",
	(t_cipher_init)aes128_init,
	(t_cipher_update)aes128_update,
	(t_cipher_final)aes128_final,
	&g_cipher_mod_ctr128, 16, 16, sizeof(t_aes_ctx)};

int	aes128_init(t_aes_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aes_keyschedule(ctx, key, 16);
	ctx->key_len = 16;
	return (1);
}

int	aes128_update(t_aes_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aes_decrypt(ctx, block);
	else
		aes_encrypt(ctx, block);
	return (1);
}

int	aes128_final(t_aes_ctx *ctx)
{
	(void)ctx;
	return (1);
}
