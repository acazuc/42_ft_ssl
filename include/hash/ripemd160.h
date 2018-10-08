/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripemd160.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:54:14 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:22:52 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIPEMD160_H
# define RIPEMD160_H

# include "hash.h"

typedef struct	s_ripemd160_ctx
{
	uint32_t	h[5];
	uint32_t	data[16];
	uint32_t	data_len;
	uint32_t	total_len;
}				t_ripemd160_ctx;

int				ripemd160_init(t_ripemd160_ctx *ctx);
int				ripemd160_update(t_ripemd160_ctx *ctx, const uint8_t *data
		, size_t len);
int				ripemd160_final(uint8_t *md, t_ripemd160_ctx *ctx);

extern t_hash	g_hash_ripemd160;

#endif
