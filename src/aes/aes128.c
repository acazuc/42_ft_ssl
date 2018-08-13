/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes128.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:13:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:06:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"

t_cipher	g_cipher_aes128_ecb = {(t_cipher_init)&aes128_init
		, (t_cipher_update)&aes128_update, (t_cipher_final)&aes128_final
		, &g_cipher_mod_ecb, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_cbc = {(t_cipher_init)&aes128_init
		, (t_cipher_update)&aes128_update, (t_cipher_final)&aes128_final
		, &g_cipher_mod_cbc, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_pcbc = {(t_cipher_init)&aes128_init
		, (t_cipher_update)&aes128_update, (t_cipher_final)&aes128_final
		, &g_cipher_mod_pcbc, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_cfb = {(t_cipher_init)&aes128_init
		, (t_cipher_update)&aes128_update, (t_cipher_final)&aes128_final
		, &g_cipher_mod_cfb, 16, 16, sizeof(t_aes_ctx)};
t_cipher	g_cipher_aes128_ofb = {(t_cipher_init)&aes128_init
		, (t_cipher_update)&aes128_update, (t_cipher_final)&aes128_final
		, &g_cipher_mod_ofb, 16, 16, sizeof(t_aes_ctx)};

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
