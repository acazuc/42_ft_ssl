/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripemd128.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 13:18:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 13:23:05 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIPEMD128_H
# define RIPEMD128_H

# include "hash.h"

typedef struct		s_ripemd128_ctx
{
	uint32_t	h[4];
	uint32_t	data[16];
	uint32_t	data_len;
	uint32_t	total_len;
}			t_ripemd128_ctx;

int	ripemd128_init(t_ripemd128_ctx *ctx);
int	ripemd128_update(t_ripemd128_ctx *ctx, const uint8_t *data, size_t len);
int	ripemd128_final(uint8_t *md, t_ripemd128_ctx *ctx);

extern t_hash		g_hash_ripemd128;

#endif
