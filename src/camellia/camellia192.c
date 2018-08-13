/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia192.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:07:46 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 21:40:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"

t_cipher	g_cipher_camellia192_ecb = {"CAMELLIA-192-ECB"
		, (t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, &g_cipher_mod_ecb, 16, 24, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia192_cbc = {"CAMELLIA-192-CBC"
		, (t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, &g_cipher_mod_cbc, 16, 24, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia192_pcbc = {"CAMELLIA-192-PCBC"
		, (t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, &g_cipher_mod_pcbc, 16, 24, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia192_cfb = {"CAMELLIA-192-CFB"
		, (t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, &g_cipher_mod_cfb, 16, 24, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia192_ofb = {"CAMELLIA-192-OFB"
		, (t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, &g_cipher_mod_ofb, 16, 24, sizeof(t_camellia_ctx)};
t_cipher	g_cipher_camellia192_ctr = {"CAMELLIA-192-CTR"
		, (t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, &g_cipher_mod_ctr128, 16, 24, sizeof(t_camellia_ctx)};

int	camellia192_init(t_camellia_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	camellia_keyschedule(ctx, key, 24);
	ctx->key_len = 24;
	return (1);
}

int	camellia192_update(t_camellia_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		camellia_decrypt(ctx, block);
	else
		camellia_encrypt(ctx, block);
	return (1);
}

int	camellia192_final(t_camellia_ctx *ctx)
{
	(void)ctx;
	return (1);
}
