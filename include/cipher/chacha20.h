/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chacha20.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 10:44:47 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 11:53:56 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHACHA20_H
# define CHACHA20_H

# include "cipher.h"

typedef struct		s_chacha20_ctx
{
	uint32_t	state[16];
}			t_chacha20_ctx;

void		chacha20_init_state(t_chacha20_ctx *ctx, uint8_t *key, uint8_t *iv);
void		chacha20_operate_block(t_chacha20_ctx *ctx, uint8_t *block);

int		chacha20_init(t_chacha20_ctx *ctx, uint8_t *key, uint8_t *iv);
int		chacha20_update(t_chacha20_ctx *ctx, uint8_t *block, int mode);
int		chacha20_final(t_chacha20_ctx *ctx);

extern t_cipher		g_cipher_chacha20;

#endif
