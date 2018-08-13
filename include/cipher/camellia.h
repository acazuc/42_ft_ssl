/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 16:46:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 23:20:58 by acazuc           ###   ########.fr       */
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
}		t_camellia_ctx;

void		camellia_operate_block(t_camellia_ctx *ctx, uint8_t *block);
uint64_t	camellia_f(uint64_t in1, uint64_t in2);
uint64_t	camellia_fl(uint64_t in1, uint64_t in2);
uint64_t	camellia_flinv(uint64_t in1, uint64_t in2);
void		camellia_keyschedule(t_camellia_ctx *ctx, uint8_t *key, uint8_t len);
void		camellia_encrypt(t_camellia_ctx *ctx, uint8_t *block);
void		camellia_decrypt(t_camellia_ctx *ctx, uint8_t *block);

int		camellia128_init(t_camellia_ctx *ctx, uint8_t *key, uint8_t *iv);
int		camellia128_update(t_camellia_ctx *ctx, uint8_t *block, int mode);
int		camellia128_final(t_camellia_ctx *ctx);
int		camellia192_init(t_camellia_ctx *ctx, uint8_t *key, uint8_t *iv);
int		camellia192_update(t_camellia_ctx *ctx, uint8_t *block, int mode);
int		camellia192_final(t_camellia_ctx *ctx);
int		camellia256_init(t_camellia_ctx *ctx, uint8_t *key, uint8_t *iv);
int		camellia256_update(t_camellia_ctx *ctx, uint8_t *block, int mode);
int		camellia256_final(t_camellia_ctx *ctx);

extern t_cipher		g_cipher_camellia128;
extern t_cipher		g_cipher_camellia192;
extern t_cipher		g_cipher_camellia256;

#endif
