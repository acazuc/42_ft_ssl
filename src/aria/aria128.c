/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aria128.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:33:11 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:36:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"

t_cipher	g_cipher_aria128_ecb = {"ARIA-128-ECB",
	(t_cipher_init)aria128_init,
	(t_cipher_update)aria128_update,
	(t_cipher_final)aria128_final,
	&g_cipher_mod_ecb, 16, 16, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria128_cbc = {"ARIA-128-CBC",
	(t_cipher_init)aria128_init,
	(t_cipher_update)aria128_update,
	(t_cipher_final)aria128_final,
	&g_cipher_mod_cbc, 16, 16, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria128_pcbc = {"ARIA-128-PCBC",
	(t_cipher_init)aria128_init,
	(t_cipher_update)aria128_update,
	(t_cipher_final)aria128_final,
	&g_cipher_mod_pcbc, 16, 16, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria128_cfb = {"ARIA-128-CFB",
	(t_cipher_init)aria128_init,
	(t_cipher_update)aria128_update,
	(t_cipher_final)aria128_final,
	&g_cipher_mod_cfb, 16, 16, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria128_ofb = {"ARIA-128-OFB",
	(t_cipher_init)aria128_init,
	(t_cipher_update)aria128_update,
	(t_cipher_final)aria128_final,
	&g_cipher_mod_ofb, 16, 16, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria128_ctr = {"ARIA-128-CTR",
	(t_cipher_init)aria128_init,
	(t_cipher_update)aria128_update,
	(t_cipher_final)aria128_final,
	&g_cipher_mod_ctr128, 16, 16, sizeof(t_aria_ctx)};

int	aria128_init(t_aria_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aria_keyschedule(ctx, key, 16);
	ctx->key_len = 16;
	return (1);
}

int	aria128_update(t_aria_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aria_decrypt(ctx, block);
	else
		aria_encrypt(ctx, block);
	return (1);
}

int	aria128_final(t_aria_ctx *ctx)
{
	(void)ctx;
	return (1);
}
