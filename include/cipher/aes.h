/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:11:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:13:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include "cipher.h"

typedef struct	s_aes_ctx
{
	uint8_t	keys[15][16];
	uint8_t	key_len;
}		t_aes_ctx;

void		aes_encrypt(t_aes_ctx *ctx, uint8_t *block);
void		aes_decrypt(t_aes_ctx *ctx, uint8_t *block);
uint8_t		aes_subbyte(uint8_t val);
void		aes_subbytes(uint8_t *block);
void		aes_invsubbytes(uint8_t *block);
void		aes_shiftrows(uint8_t *block);
void		aes_invshiftrows(uint8_t *block);
void		aes_mixcolumns(uint8_t *block);
void		aes_invmixcolumns(uint8_t *block);
void		aes_keyschedule(t_aes_ctx *ctx, uint8_t *key, uint8_t len);
uint8_t		aes_rcon(uint8_t val);

int		aes128_init(t_aes_ctx *ctx, uint8_t *key, uint8_t *iv);
int		aes128_update(t_aes_ctx *ctx, uint8_t *block, int mode);
int		aes128_final(t_aes_ctx *ctx);
int		aes192_init(t_aes_ctx *ctx, uint8_t *key, uint8_t *iv);
int		aes192_update(t_aes_ctx *ctx, uint8_t *block, int mode);
int		aes192_final(t_aes_ctx *ctx);
int		aes256_init(t_aes_ctx *ctx, uint8_t *key, uint8_t *iv);
int		aes256_update(t_aes_ctx *ctx, uint8_t *block, int mode);
int		aes256_final(t_aes_ctx *ctx);

extern t_cipher		g_cipher_aes128_ecb;
extern t_cipher		g_cipher_aes128_cbc;
extern t_cipher		g_cipher_aes128_pcbc;
extern t_cipher		g_cipher_aes128_cfb;
extern t_cipher		g_cipher_aes128_ofb;
extern t_cipher		g_cipher_aes192_ecb;
extern t_cipher		g_cipher_aes192_cbc;
extern t_cipher		g_cipher_aes192_pcbc;
extern t_cipher		g_cipher_aes192_cfb;
extern t_cipher		g_cipher_aes192_ofb;
extern t_cipher		g_cipher_aes256_ecb;
extern t_cipher		g_cipher_aes256_cbc;
extern t_cipher		g_cipher_aes256_pcbc;
extern t_cipher		g_cipher_aes256_cfb;
extern t_cipher		g_cipher_aes256_ofb;

#endif
