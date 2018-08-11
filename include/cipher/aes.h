/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:11:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:46:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include "cipher.h"
# include <stdint.h>
# include <stddef.h>

typedef struct	s_aes_ctx
{
	uint8_t	keys[15][16];
	uint8_t	key_len;
}		t_aes_ctx;

typedef struct	s_aes128_ctx
{
	t_aes_ctx	ctx;
}		t_aes128_ctx;

typedef struct	s_aes192_ctx
{
	t_aes_ctx	ctx;
}		t_aes192_ctx;

typedef struct	s_aes256_ctx
{
	t_aes_ctx	ctx;
}		t_aes256_ctx;

void		aes_encrypt(t_aes_ctx *ctx, uint8_t *block);
void		aes_decrypt(t_aes_ctx *ctx, uint8_t *block);
uint8_t		aes_subbyte(uint8_t val);
void		aes_subbytes(uint8_t *block);
void		aes_invsubbytes(uint8_t *block);
void		aes_shiftrows(uint8_t *block);
void		aes_invshiftrows(uint8_t *block);
void		aes_mixcolumns(uint8_t *block);
void		aes_invmixcolumns(uint8_t *block);
void		aes_keyexpand(t_aes_ctx *ctx, uint8_t *key, uint8_t len);
uint8_t		aes_rcon(uint8_t val);

int		aes128_init(t_aes128_ctx *ctx, uint8_t *key);
int		aes128_update(t_aes128_ctx *ctx, uint8_t *block, int mode);
int		aes128_final(t_aes128_ctx *ctx);
int		aes192_init(t_aes192_ctx *ctx, uint8_t *key);
int		aes192_update(t_aes192_ctx *ctx, uint8_t *block, int mode);
int		aes192_final(t_aes192_ctx *ctx);
int		aes256_init(t_aes256_ctx *ctx, uint8_t *key);
int		aes256_update(t_aes256_ctx *ctx, uint8_t *block, int mode);
int		aes256_final(t_aes256_ctx *ctx);

extern t_cipher		g_cipher_aes128;
extern t_cipher		g_cipher_aes192;
extern t_cipher		g_cipher_aes256;

#endif
