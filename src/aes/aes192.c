/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes192.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:14:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 19:14:26 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"

t_cipher	g_cipher_aes192 = {(t_cipher_init)&aes192_init
		, (t_cipher_update)&aes192_update, (t_cipher_final)&aes192_final
		, 16, 24, sizeof(t_aes_ctx)};

int	aes192_init(t_aes_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	aes_keyschedule(ctx, key, 24);
	ctx->key_len = 24;
	return (1);
}

int	aes192_update(t_aes_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
		aes_decrypt(ctx, block);
	else
		aes_encrypt(ctx, block);
	return (1);
}

int	aes192_final(t_aes_ctx *ctx)
{
	(void)ctx;
	return (1);
}
