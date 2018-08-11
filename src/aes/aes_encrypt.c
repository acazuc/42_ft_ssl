/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes_encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:36:49 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:09:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"
#include "libft.h"

int	aes_encrypt_init(t_aes_ctx *ctx, uint8_t *key, uint8_t key_len)
{
	if (key_len == 16)
		aes_keyexpand(ctx, key, 16);
	else if (key_len == 24)
		aes_keyexpand(ctx, key, 24);
	else if (key_len == 32)
		aes_keyexpand(ctx, key, 32);
	else
		return (0);
	ctx->key_len = key_len;
	return (1);
}

int	aes_encrypt_update(t_aes_ctx *ctx, uint8_t *data, size_t len)
{
	(void)len;
	aes_encrypt(ctx, data);
	return (1);
}

int	aes_encrypt_final(t_aes_ctx *ctx)
{
	(void)ctx;
	return (1);
}
