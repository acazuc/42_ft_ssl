/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aria192.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:33:13 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 16:48:13 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"

t_cipher	g_cipher_aria192_ecb = {"ARIA-192-ECB",
	(t_cipher_init)aria192_init,
	(t_cipher_update)aria192_update,
	(t_cipher_final)aria192_final,
	&g_cipher_mod_ecb, 16, 24, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria192_cbc = {"ARIA-192-CBC",
	(t_cipher_init)aria192_init,
	(t_cipher_update)aria192_update,
	(t_cipher_final)aria192_final,
	&g_cipher_mod_cbc, 16, 24, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria192_pcbc = {"ARIA-192-PCBC",
	(t_cipher_init)aria192_init,
	(t_cipher_update)aria192_update,
	(t_cipher_final)aria192_final,
	&g_cipher_mod_pcbc, 16, 24, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria192_cfb = {"ARIA-192-CFB",
	(t_cipher_init)aria192_init,
	(t_cipher_update)aria192_update,
	(t_cipher_final)aria192_final,
	&g_cipher_mod_cfb, 16, 24, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria192_ofb = {"ARIA-192-OFB",
	(t_cipher_init)aria192_init,
	(t_cipher_update)aria192_update,
	(t_cipher_final)aria192_final,
	&g_cipher_mod_ofb, 16, 24, sizeof(t_aria_ctx)};
t_cipher	g_cipher_aria192_ctr = {"ARIA-192-CTR",
	(t_cipher_init)aria192_init,
	(t_cipher_update)aria192_update,
	(t_cipher_final)aria192_final,
	&g_cipher_mod_ctr128, 16, 24, sizeof(t_aria_ctx)};

int	aria192_init(t_aria_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aria_keyschedule(ctx, key, 24);
	ctx->key_len = 24;
	return (1);
}

int	aria192_update(t_aria_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aria_decrypt(ctx, block);
	else
		aria_encrypt(ctx, block);
	return (1);
}

int	aria192_final(t_aria_ctx *ctx)
{
	(void)ctx;
	return (1);
}
