/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:25:12 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 12:28:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha512.h"
#include "ft_ssl.h"
#include "pem.h"

int	pem_get_key(t_cipher_ctx *ctx, uint8_t *key, uint8_t *salt_iv
		, char *password)
{
	t_pbkdf2_ctx	pbkdf2_ctx;

	pbkdf2_ctx.h.hash = &g_hash_sha512;
	pbkdf2_ctx.salt = salt_iv;
	pbkdf2_ctx.salt_len = FT_MAX(8, ctx->cipher->block_size);
	pbkdf2_ctx.password = (uint8_t*)password;
	pbkdf2_ctx.password_len = ft_strlen(password);
	pbkdf2_ctx.iterations = 4096;
	pbkdf2_ctx.out = key;
	pbkdf2_ctx.out_len = ctx->cipher->key_size;
	if (!pbkdf2(&pbkdf2_ctx))
		return (0);
	return (1);
}
