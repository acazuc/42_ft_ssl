/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md4.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:13:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:10:37 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD4_H
# define MD4_H

# include "hash.h"

typedef struct	s_md4_ctx
{
	uint32_t	h[4];
	uint32_t	data[16];
	uint32_t	data_len;
	uint64_t	total_len;
}				t_md4_ctx;

int				md4_init(t_md4_ctx *ctx);
int				md4_update(t_md4_ctx *ctx, const uint8_t *data, size_t len);
int				md4_final(uint8_t *md, t_md4_ctx *ctx);

extern t_hash	g_hash_md4;

#endif
