/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:11:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 22:38:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

# include <stdint.h>

typedef struct	s_aes_ctx
{
	uint8_t	key[16];
}		t_aes_ctx;

void		aes_operate_block(t_aes_ctx *ctx, uint8_t *block, int mode);
void		aes_subbytes(uint8_t *block);
void		aes_invsubbytes(uint8_t *block);
void		aes_shiftrows(uint8_t *block);
void		aes_mixcolumns(uint8_t *block);

#endif
