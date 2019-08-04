/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aria.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:27:06 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 16:20:34 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARIA_H
# define ARIA_H

# include "cipher.h"

typedef struct	s_aria_ctx
{
	uint8_t		ekeys[17][16];
	uint8_t		dkeys[17][16];
	uint8_t		key_len;
}			t_aria_ctx;

void			aria_encrypt(t_aria_ctx *ctx, uint8_t *block);
void			aria_decrypt(t_aria_ctx *ctx, uint8_t *block);
void			aria_keyschedule(t_aria_ctx *ctx, uint8_t *key, uint8_t len);
void			aria_sl1(uint8_t *dst, uint8_t *src);
void			aria_sl2(uint8_t *dst, uint8_t *src);
void			aria_a(uint8_t *dst, uint8_t *src);
void			aria_fo(uint8_t *dst, uint8_t *d, uint8_t *rk);
void			aria_fe(uint8_t *dst, uint8_t *d, uint8_t *rk);

int				aria128_init(t_aria_ctx *ctx, uint8_t *key, uint8_t *iv);
int				aria128_update(t_aria_ctx *ctx, uint8_t *block, int mode);
int				aria128_final(t_aria_ctx *ctx);
int				aria192_init(t_aria_ctx *ctx, uint8_t *key, uint8_t *iv);
int				aria192_update(t_aria_ctx *ctx, uint8_t *block, int mode);
int				aria192_final(t_aria_ctx *ctx);
int				aria256_init(t_aria_ctx *ctx, uint8_t *key, uint8_t *iv);
int				aria256_update(t_aria_ctx *ctx, uint8_t *block, int mode);
int				aria256_final(t_aria_ctx *ctx);

extern t_cipher		g_cipher_aria128_ecb;
extern t_cipher		g_cipher_aria128_cbc;
extern t_cipher		g_cipher_aria128_pcbc;
extern t_cipher		g_cipher_aria128_cfb;
extern t_cipher		g_cipher_aria128_ofb;
extern t_cipher		g_cipher_aria128_ctr;
extern t_cipher		g_cipher_aria192_ecb;
extern t_cipher		g_cipher_aria192_cbc;
extern t_cipher		g_cipher_aria192_pcbc;
extern t_cipher		g_cipher_aria192_cfb;
extern t_cipher		g_cipher_aria192_ofb;
extern t_cipher		g_cipher_aria192_ctr;
extern t_cipher		g_cipher_aria256_ecb;
extern t_cipher		g_cipher_aria256_cbc;
extern t_cipher		g_cipher_aria256_pcbc;
extern t_cipher		g_cipher_aria256_cfb;
extern t_cipher		g_cipher_aria256_ofb;
extern t_cipher		g_cipher_aria256_ctr;

#endif
