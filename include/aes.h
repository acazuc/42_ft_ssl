/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:11:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 16:15:26 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include <stdint.h>
# include <stddef.h>

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
void		aes_keyexpand(t_aes_ctx *ctx, uint8_t *key, uint8_t len);
uint8_t		aes_rcon(uint8_t val);

int		aes_encrypt_init(t_aes_ctx *ctx, uint8_t *key, uint8_t key_len);
int		aes_encrypt_update(t_aes_ctx *ctx, uint8_t *data, size_t len);
int		aes_encrypt_final(t_aes_ctx *ctx);
int		aes_decrypt_init(t_aes_ctx *ctx, uint8_t *key, uint8_t key_len);
int		aes_decrypt_update(t_aes_ctx *ctx, uint8_t *data, size_t len);
int		aes_decrypt_final(t_aes_ctx *ctx);

#endif
