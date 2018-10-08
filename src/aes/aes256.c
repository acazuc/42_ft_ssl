/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:15:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 12:29:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"

t_cipher	g_cipher_aes256_ecb = {"AES-256-ECB",
	(t_cipher_init)aes256_init,
	(t_cipher_update)aes256_update,
	(t_cipher_final)aes256_final,
	&g_cipher_mod_ecb, 16, 32, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes256_cbc = {"AES-256-CBC",
	(t_cipher_init)aes256_init,
	(t_cipher_update)aes256_update,
	(t_cipher_final)aes256_final,
	&g_cipher_mod_cbc, 16, 32, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes256_pcbc = {"AES-256-PCBC",
	(t_cipher_init)aes256_init,
	(t_cipher_update)aes256_update,
	(t_cipher_final)aes256_final,
	&g_cipher_mod_pcbc, 16, 32, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes256_cfb = {"AES-256-CFB",
	(t_cipher_init)aes256_init,
	(t_cipher_update)aes256_update,
	(t_cipher_final)aes256_final,
	&g_cipher_mod_cfb, 16, 32, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes256_ofb = {"AES-256-OFB",
	(t_cipher_init)aes256_init,
	(t_cipher_update)aes256_update,
	(t_cipher_final)aes256_final,
	&g_cipher_mod_ofb, 16, 32, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes256_ctr = {"AES-256-CTR",
	(t_cipher_init)aes256_init,
	(t_cipher_update)aes256_update,
	(t_cipher_final)aes256_final,
	&g_cipher_mod_ctr128, 16, 32, sizeof(t_aes_ctx)};

int	aes256_init(t_aes_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aes_keyschedule(ctx, key, 32);
	ctx->key_len = 32;
	return (1);
}

int	aes256_update(t_aes_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aes_decrypt(ctx, block);
	else
		aes_encrypt(ctx, block);
	return (1);
}

int	aes256_final(t_aes_ctx *ctx)
{
	(void)ctx;
	return (1);
}
