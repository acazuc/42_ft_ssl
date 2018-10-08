/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:46:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:19:05 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMELLIA_H
# define CAMELLIA_H

# include "cipher.h"

typedef struct	s_camellia_ctx
{
	uint8_t		key_len;
	uint64_t	kw[4];
	uint64_t	k[24];
	uint64_t	ke[6];
}				t_camellia_ctx;

void			camellia_operate_block(t_camellia_ctx *ctx, uint8_t *block);
uint64_t		camellia_f(uint64_t in1, uint64_t in2);
uint64_t		camellia_fl(uint64_t in1, uint64_t in2);
uint64_t		camellia_flinv(uint64_t in1, uint64_t in2);
void			camellia_keyschedule(t_camellia_ctx *ctx, uint8_t *key
		, uint8_t len);
void			camellia_keyschedule_128(t_camellia_ctx *ctx, uint8_t *klr
		, uint8_t *kab);
void			camellia_keyschedule_192_256(t_camellia_ctx *ctx, uint8_t *klr
		, uint8_t *kab);
void			camellia_encrypt(t_camellia_ctx *ctx, uint8_t *block);
void			camellia_decrypt(t_camellia_ctx *ctx, uint8_t *block);

int				camellia128_init(t_camellia_ctx *ctx, uint8_t *key
		, uint8_t *iv);
int				camellia128_update(t_camellia_ctx *ctx, uint8_t *block
		, int mode);
int				camellia128_final(t_camellia_ctx *ctx);
int				camellia192_init(t_camellia_ctx *ctx, uint8_t *key
		, uint8_t *iv);
int				camellia192_update(t_camellia_ctx *ctx, uint8_t *block
		, int mode);
int				camellia192_final(t_camellia_ctx *ctx);
int				camellia256_init(t_camellia_ctx *ctx, uint8_t *key
		, uint8_t *iv);
int				camellia256_update(t_camellia_ctx *ctx, uint8_t *block
		, int mode);
int				camellia256_final(t_camellia_ctx *ctx);

extern t_cipher		g_cipher_camellia128_ecb;
extern t_cipher		g_cipher_camellia128_cbc;
extern t_cipher		g_cipher_camellia128_pcbc;
extern t_cipher		g_cipher_camellia128_cfb;
extern t_cipher		g_cipher_camellia128_ofb;
extern t_cipher		g_cipher_camellia128_ctr;
extern t_cipher		g_cipher_camellia192_ecb;
extern t_cipher		g_cipher_camellia192_cbc;
extern t_cipher		g_cipher_camellia192_pcbc;
extern t_cipher		g_cipher_camellia192_cfb;
extern t_cipher		g_cipher_camellia192_ofb;
extern t_cipher		g_cipher_camellia192_ctr;
extern t_cipher		g_cipher_camellia256_ecb;
extern t_cipher		g_cipher_camellia256_cbc;
extern t_cipher		g_cipher_camellia256_pcbc;
extern t_cipher		g_cipher_camellia256_cfb;
extern t_cipher		g_cipher_camellia256_ofb;
extern t_cipher		g_cipher_camellia256_ctr;

#endif
