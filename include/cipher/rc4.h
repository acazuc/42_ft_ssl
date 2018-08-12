/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:08:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 14:35:23 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RC4_H
# define RC4_H

# include "cipher.h"

typedef struct	s_rc4_ctx
{
	uint8_t	state[256];
	uint8_t	i;
	uint8_t	j;
}		t_rc4_ctx;

void		rc4_init_state(t_rc4_ctx *ctx, uint8_t *key);
void		rc4_operate_block(t_rc4_ctx *ctx, uint8_t *block);

int		rc4_init(t_rc4_ctx *ctx, uint8_t *key, uint8_t *iv);
int		rc4_update(t_rc4_ctx *ctx, uint8_t *block, int mode);
int		rc4_final(t_rc4_ctx *ctx);

extern t_cipher		g_cipher_rc4;

#endif
