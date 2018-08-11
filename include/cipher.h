/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:30:34 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 19:57:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIPHER_H
# define CIPHER_H

# include <stdint.h>
# include <stddef.h>

typedef struct		s_cipher_ctx t_cipher_ctx;

typedef void (*t_cipher_mod)(t_cipher_ctx *ctx, uint8_t *data);
typedef int (*t_cipher_update)(void *userptr, uint8_t *data, size_t len);
typedef int (*t_cipher_cb)(void *userptr, uint8_t *data, size_t len);

struct			s_cipher_ctx
{
	t_cipher_mod	premod;
	t_cipher_mod	postmod;
	t_cipher_update	update;
	t_cipher_cb	callback;
	void		*userptr;
	uint32_t	block_size;
	uint32_t	buff_pos;
	uint8_t		*buff;
	uint8_t		*mod1;
	uint8_t		*mod2;
	uint8_t		*iv;
	int		nopad;
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
int		cipher_init(t_cipher_ctx *ctx, uint32_t block_size);
int		cipher_update(t_cipher_ctx *ctx, uint8_t *data, size_t len);
int		cipher_final(t_cipher_ctx *ctx);

#endif
