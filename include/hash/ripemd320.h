/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripemd320.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 14:20:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 15:03:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIPEMD320_H
# define RIPEMD320_H

# include "hash.h"

typedef struct		s_ripemd320_ctx
{
	uint32_t	h[10];
	uint32_t	data[16];
	uint32_t	data_len;
	uint32_t	total_len;
}			t_ripemd320_ctx;

int	ripemd320_init(t_ripemd320_ctx *ctx);
int	ripemd320_update(t_ripemd320_ctx *ctx, const uint8_t *data, size_t len);
int	ripemd320_final(uint8_t *md, t_ripemd320_ctx *ctx);

extern t_hash		g_hash_ripemd320;

#endif
