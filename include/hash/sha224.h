/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:53:55 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:39:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
# define SHA224_H

# include "hash.h"

typedef struct		s_sha224_ctx
{
	uint32_t	h[8];
	uint32_t	data[16];
	uint32_t	data_len;
	uint64_t	total_len;
}			t_sha224_ctx;

int	sha224_init(t_sha224_ctx *ctx);
int	sha224_update(t_sha224_ctx *ctx, const uint8_t *data, size_t len);
int	sha224_final(uint8_t *md, t_sha224_ctx *ctx);

extern t_hash		g_hash_sha224;

#endif
