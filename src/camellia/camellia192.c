/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia192.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:07:46 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 19:15:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"

t_cipher	g_cipher_camellia192 = {(t_cipher_init)&camellia192_init
		, (t_cipher_update)&camellia192_update
		, (t_cipher_final)&camellia192_final
		, 16, 24, sizeof(t_camellia_ctx)};

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
