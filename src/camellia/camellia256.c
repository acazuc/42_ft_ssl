/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:07:50 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 19:11:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"

t_cipher	g_cipher_camellia256_ecb = {"CAMELLIA-256-ECB"
		, (t_cipher_init)&camellia256_init
		, (t_cipher_update)&camellia256_update
		, (t_cipher_final)&camellia256_final
		, &g_cipher_mod_ecb, 16, 32, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia256_cbc = {"CAMELLIA-256-CBC"
		, (t_cipher_init)&camellia256_init
		, (t_cipher_update)&camellia256_update
		, (t_cipher_final)&camellia256_final
		, &g_cipher_mod_cbc, 16, 32, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia256_pcbc = {"CAMELLIA-256-PCBC"
		, (t_cipher_init)&camellia256_init
		, (t_cipher_update)&camellia256_update
		, (t_cipher_final)&camellia256_final
		, &g_cipher_mod_pcbc, 16, 32, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia256_cfb = {"CAMELLIA-256-CFB"
		, (t_cipher_init)&camellia256_init
		, (t_cipher_update)&camellia256_update
		, (t_cipher_final)&camellia256_final
		, &g_cipher_mod_cfb, 16, 32, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia256_ofb = {"CAMELLIA-256-OFB"
		, (t_cipher_init)&camellia256_init
		, (t_cipher_update)&camellia256_update
		, (t_cipher_final)&camellia256_final
		, &g_cipher_mod_ofb, 16, 32, sizeof(t_camellia_ctx)};

int	camellia256_init(t_camellia_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	camellia_keyschedule(ctx, key, 32);
	ctx->key_len = 32;
	return (1);
}

int	camellia256_update(t_camellia_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		camellia_decrypt(ctx, block);
	else
		camellia_encrypt(ctx, block);
	return (1);
}

int	camellia256_final(t_camellia_ctx *ctx)
{
	(void)ctx;
	return (1);
}
