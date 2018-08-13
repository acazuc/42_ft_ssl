/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 20:52:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 21:48:54 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "libft.h"

t_cipher	g_cipher_des3_ecb = {"DES-EDE3-ECB"
		, (t_cipher_init)&des3_init
		, (t_cipher_update)&des3_update
		, (t_cipher_final)&des3_final
		, &g_cipher_mod_ecb, 8, 24, sizeof(t_des3_ctx)};
t_cipher	g_cipher_des3_cbc = {"DES-EDE3-CBC"
		, (t_cipher_init)&des3_init
		, (t_cipher_update)&des3_update
		, (t_cipher_final)&des3_final
		, &g_cipher_mod_cbc, 8, 24, sizeof(t_des3_ctx)};
t_cipher	g_cipher_des3_pcbc = {"DES-EDE3-PCBC"
		, (t_cipher_init)&des3_init
		, (t_cipher_update)&des3_update
		, (t_cipher_final)&des3_final
		, &g_cipher_mod_pcbc, 8, 24, sizeof(t_des3_ctx)};
t_cipher	g_cipher_des3_cfb = {"DES-EDE3-CFB"
		, (t_cipher_init)&des3_init
		, (t_cipher_update)&des3_update
		, (t_cipher_final)&des3_final
		, &g_cipher_mod_cfb, 8, 24, sizeof(t_des3_ctx)};
t_cipher	g_cipher_des3_ofb = {"DES-EDE3-OFB"
		, (t_cipher_init)&des3_init
		, (t_cipher_update)&des3_update
		, (t_cipher_final)&des3_final
		, &g_cipher_mod_ofb, 8, 24, sizeof(t_des3_ctx)};
t_cipher	g_cipher_des3_ctr = {"DES-EDE3-CTR"
		, (t_cipher_init)&des3_init
		, (t_cipher_update)&des3_update
		, (t_cipher_final)&des3_final
		, &g_cipher_mod_ctr64, 8, 24, sizeof(t_des3_ctx)};

int	des3_init(t_des3_ctx *ctx, uint8_t *key, uint8_t *iv)
{
	(void)iv;
	des_generate_keys(&ctx->ctx1, ft_swap_ulong(*(uint64_t*)key));
	des_generate_keys(&ctx->ctx2, ft_swap_ulong(*(uint64_t*)(key + 8)));
	des_generate_keys(&ctx->ctx3, ft_swap_ulong(*(uint64_t*)(key + 16)));
	return (1);
}

int	des3_update(t_des3_ctx *ctx, uint8_t *block, int mode)
{
	if (mode)
	{
		des_operate_block(&ctx->ctx3, (uint64_t*)block, mode);
		des_operate_block(&ctx->ctx2, (uint64_t*)block, !mode);
		des_operate_block(&ctx->ctx1, (uint64_t*)block, mode);
	}
	else
	{
		des_operate_block(&ctx->ctx1, (uint64_t*)block, mode);
		des_operate_block(&ctx->ctx2, (uint64_t*)block, !mode);
		des_operate_block(&ctx->ctx3, (uint64_t*)block, mode);
	}
	return (1);
}

int	des3_final(t_des3_ctx *ctx)
{
	(void)ctx;
	return (1);
}
