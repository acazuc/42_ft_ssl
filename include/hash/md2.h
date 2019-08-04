/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md2.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:53:07 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 17:32:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD2_H
# define MD2_H

# include "hash.h"

typedef struct	s_md2_ctx
{
	uint8_t	h[16];
	uint8_t	data[16];
	uint8_t	checksum[16];
	uint32_t	data_len;
	uint32_t	total_len;
}				t_md2_ctx;

int			md2_init(t_md2_ctx *ctx);
int			md2_update(t_md2_ctx *ctx, const uint8_t *data, size_t len);
int			md2_final(uint8_t *md, t_md2_ctx *ctx);

extern t_hash	g_hash_md2;

#endif
