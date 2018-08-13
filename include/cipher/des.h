/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:26:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 21:48:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "cipher.h"

typedef struct		s_des_ctx
{
	uint64_t	keys[16];
}			t_des_ctx;

typedef struct		s_des1_ctx
{
	t_des_ctx	ctx1;
}			t_des1_ctx;

typedef struct		s_des2_ctx
{
	t_des_ctx	ctx1;
	t_des_ctx	ctx2;
}			t_des2_ctx;

typedef struct		s_des3_ctx
{
	t_des_ctx	ctx1;
	t_des_ctx	ctx2;
	t_des_ctx	ctx3;
}			t_des3_ctx;

void	des_generate_keys(t_des_ctx *ctx, uint64_t key);
void	des_operate_block(t_des_ctx *ctx, uint64_t *block, int mode);

int	des1_init(t_des1_ctx *ctx, uint8_t *key, uint8_t *iv);
int	des1_update(t_des1_ctx *ctx, uint8_t *block, int mode);
int	des1_final(t_des1_ctx *ctx);
int	des2_init(t_des2_ctx *ctx, uint8_t *key, uint8_t *iv);
int	des2_update(t_des2_ctx *ctx, uint8_t *block, int mode);
int	des2_final(t_des2_ctx *ctx);
int	des3_init(t_des3_ctx *ctx, uint8_t *key, uint8_t *iv);
int	des3_update(t_des3_ctx *ctx, uint8_t *block, int mode);
int	des3_final(t_des3_ctx *ctx);

extern t_cipher		g_cipher_des1_ecb;
extern t_cipher		g_cipher_des1_cbc;
extern t_cipher		g_cipher_des1_pcbc;
extern t_cipher		g_cipher_des1_cfb;
extern t_cipher		g_cipher_des1_ofb;
extern t_cipher		g_cipher_des1_ctr;
extern t_cipher		g_cipher_des2_ecb;
extern t_cipher		g_cipher_des2_cbc;
extern t_cipher		g_cipher_des2_pcbc;
extern t_cipher		g_cipher_des2_cfb;
extern t_cipher		g_cipher_des2_ofb;
extern t_cipher		g_cipher_des2_ctr;
extern t_cipher		g_cipher_des3_ecb;
extern t_cipher		g_cipher_des3_cbc;
extern t_cipher		g_cipher_des3_pcbc;
extern t_cipher		g_cipher_des3_cfb;
extern t_cipher		g_cipher_des3_ofb;
extern t_cipher		g_cipher_des3_ctr;

#endif
