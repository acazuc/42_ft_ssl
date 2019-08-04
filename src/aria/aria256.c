/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aria256.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:33:15 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:37:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"

t_cipher	g_cipher_aria256_ecb = {"ARIA-256-ECB",
	(t_cipher_init)aria256_init,
	(t_cipher_update)aria256_update,
	(t_cipher_final)aria256_final,
	&g_cipher_mod_ecb, 16, 32, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria256_cbc = {"ARIA-256-CBC",
	(t_cipher_init)aria256_init,
	(t_cipher_update)aria256_update,
	(t_cipher_final)aria256_final,
	&g_cipher_mod_cbc, 16, 32, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria256_pcbc = {"ARIA-256-PCBC",
	(t_cipher_init)aria256_init,
	(t_cipher_update)aria256_update,
	(t_cipher_final)aria256_final,
	&g_cipher_mod_pcbc, 16, 32, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria256_cfb = {"ARIA-256-CFB",
	(t_cipher_init)aria256_init,
	(t_cipher_update)aria256_update,
	(t_cipher_final)aria256_final,
	&g_cipher_mod_cfb, 16, 32, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria256_ofb = {"ARIA-256-OFB",
	(t_cipher_init)aria256_init,
	(t_cipher_update)aria256_update,
	(t_cipher_final)aria256_final,
	&g_cipher_mod_ofb, 16, 32, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria256_ctr = {"ARIA-256-CTR",
	(t_cipher_init)aria256_init,
	(t_cipher_update)aria256_update,
	(t_cipher_final)aria256_final,
	&g_cipher_mod_ctr128, 16, 32, sizeof(t_aria_ctx)};

int	aria256_init(t_aria_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aria_keyschedule(ctx, key, 32);
	ctx->key_len = 32;
	return (1);
}

int	aria256_update(t_aria_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aria_decrypt(ctx, block);
	else
		aria_encrypt(ctx, block);
	return (1);
}

int	aria256_final(t_aria_ctx *ctx)
{
	(void)ctx;
	return (1);
}
