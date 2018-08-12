/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:30:34 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 12:13:23 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIPHER_H
# define CIPHER_H

# include <stdint.h>
# include <stddef.h>

typedef struct		s_cipher_ctx t_cipher_ctx;

typedef int (*t_cipher_init)(void *ctx, uint8_t *key, uint8_t *iv);
typedef int (*t_cipher_update)(void *ctx, uint8_t *data, int mode);
typedef int (*t_cipher_final)(void *ctx);
typedef void (*t_cipher_mod_fn)(t_cipher_ctx *ctx, uint8_t *data);
typedef int (*t_cipher_cb)(void *userptr, uint8_t *data, size_t len);

typedef struct		s_cipher
{
	t_cipher_init	init;
	t_cipher_update	update;
	t_cipher_final	final;
	uint32_t	block_size;
	uint32_t	key_size;
	uint32_t	ctx_size;
}			t_cipher;

typedef struct		s_cipher_mod
{
	t_cipher_mod_fn	premod;
	t_cipher_mod_fn	postmod;
	int		nopad;
}			t_cipher_mod;

struct			s_cipher_ctx
{
	t_cipher	*cipher;
	t_cipher_mod	*mod;
	t_cipher_cb	callback;
	void		*ctx;
	void		*userptr;
	uint32_t	buff_pos;
	uint8_t		*buff;
	uint8_t		*mod1;
	uint8_t		*mod2;
	int		ended;
	int		mode;
	int		mod3;
};

void		cipher_ecb_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_ecb_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cbc_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cbc_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_pcbc_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_pcbc_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cfb_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cfb_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_ofb_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_ofb_postmod(t_cipher_ctx *ctx, uint8_t *data);
int		cipher_init(t_cipher_ctx *ctx, uint8_t *key, uint8_t *iv);
int		cipher_update(t_cipher_ctx *ctx, uint8_t *data, size_t len);
int		cipher_final(t_cipher_ctx *ctx);

extern t_cipher_mod	g_cipher_mod_ecb;
extern t_cipher_mod	g_cipher_mod_ecb_nopad;
extern t_cipher_mod	g_cipher_mod_cbc;
extern t_cipher_mod	g_cipher_mod_pcbc;
extern t_cipher_mod	g_cipher_mod_cfb;
extern t_cipher_mod	g_cipher_mod_ofb;

#endif
