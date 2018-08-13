/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:43:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 21:48:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "libft.h"

t_cipher	g_cipher_des1_ecb = {"DES-ECB"
		, (t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update
		, (t_cipher_final)&des1_final
		, &g_cipher_mod_ecb, 8, 8, sizeof(t_des1_ctx)};
t_cipher	g_cipher_des1_cbc = {"DES-CBC"
		, (t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update
		, (t_cipher_final)&des1_final
		, &g_cipher_mod_cbc, 8, 8, sizeof(t_des1_ctx)};
t_cipher	g_cipher_des1_pcbc = {"DES-PCBC"
		, (t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update
		, (t_cipher_final)&des1_final
		, &g_cipher_mod_pcbc, 8, 8, sizeof(t_des1_ctx)};
t_cipher	g_cipher_des1_cfb = {"DES-CFB"
		, (t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update
		, (t_cipher_final)&des1_final
		, &g_cipher_mod_cfb, 8, 8, sizeof(t_des1_ctx)};
t_cipher	g_cipher_des1_ofb = {"DES-OFB"
		, (t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update
		, (t_cipher_final)&des1_final
		, &g_cipher_mod_ofb, 8, 8, sizeof(t_des1_ctx)};
t_cipher	g_cipher_des1_ctr = {"DES-CTR"
		, (t_cipher_init)&des1_init
		, (t_cipher_update)&des1_update
		, (t_cipher_final)&des1_final
		, &g_cipher_mod_ctr64, 8, 8, sizeof(t_des1_ctx)};

int	des1_init(t_des1_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	des_generate_keys(&ctx->ctx1, ft_swap_ulong(*(uint64_t*)key));
	return (1);
}

int	des1_update(t_des1_ctx *ctx, uint8_t *block, int mode)
{
	des_operate_block(&ctx->ctx1, (uint64_t*)block, mode);
	return (1);
}

int	des1_final(t_des1_ctx *ctx)
{
	(void)ctx;
	return (1);
}
