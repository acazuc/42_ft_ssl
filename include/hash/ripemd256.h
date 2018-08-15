/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripemd256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:03:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 15:03:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIPEMD256_H
# define RIPEMD256_H

# include "hash.h"

typedef struct		s_ripemd256_ctx
{
	uint32_t	h[8];
	uint32_t	data[16];
	uint32_t	data_len;
	uint32_t	total_len;
}			t_ripemd256_ctx;

int	ripemd256_init(t_ripemd256_ctx *ctx);
int	ripemd256_update(t_ripemd256_ctx *ctx, const uint8_t *data, size_t len);
int	ripemd256_final(uint8_t *md, t_ripemd256_ctx *ctx);

extern t_hash		g_hash_ripemd256;

#endif
