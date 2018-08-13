/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia128.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:07:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 00:13:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include <stdio.h>

t_cipher	g_cipher_camellia128 = {(t_cipher_init)&camellia128_init
		, (t_cipher_update)&camellia128_update
		, (t_cipher_final)&camellia128_final
		, 16, 16, sizeof(t_camellia_ctx)};

int	camellia128_init(t_camellia_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	camellia_keyschedule(ctx, key, 16);
	ctx->key_len = 16;
	return (1);
}

int	camellia128_update(t_camellia_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		camellia_decrypt(ctx, block);
	else
		camellia_encrypt(ctx, block);
	return (1);
}

int	camellia128_final(t_camellia_ctx *ctx)
{
	(void)ctx;
	return (1);
}
