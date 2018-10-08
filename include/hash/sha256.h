/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 20:57:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:23:17 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "hash.h"

typedef struct	s_sha256_ctx
{
	uint32_t	h[8];
	uint32_t	data[16];
	uint32_t	data_len;
	uint64_t	total_len;
}				t_sha256_ctx;

int				sha256_init(t_sha256_ctx *ctx);
int				sha256_update(t_sha256_ctx *ctx, const uint8_t *data
		, size_t len);
int				sha256_final(uint8_t *md, t_sha256_ctx *ctx);

extern t_hash	g_hash_sha256;

#endif
