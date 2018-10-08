/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:54:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:10:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "hash.h"

typedef struct	s_md5_ctx
{
	uint32_t	h[4];
	uint32_t	data[16];
	uint32_t	data_len;
	uint64_t	total_len;
}				t_md5_ctx;

int				md5_init(t_md5_ctx *ctx);
int				md5_update(t_md5_ctx *ctx, const uint8_t *data, size_t len);
int				md5_final(uint8_t *md, t_md5_ctx *ctx);

extern t_hash	g_hash_md5;

#endif
