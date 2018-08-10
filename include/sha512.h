/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 09:32:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:39:27 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# include "hash.h"

typedef struct		s_sha512_ctx
{
	uint64_t	h[8];
	uint64_t	data[16];
	uint64_t	data_len;
	uint64_t	total_len;
}			t_sha512_ctx;

int	sha512_init(t_sha512_ctx *ctx);
int	sha512_update(t_sha512_ctx *ctx, const uint8_t *data, size_t len);
int	sha512_final(uint8_t *md, t_sha512_ctx *ctx);

extern t_hash		g_hash_sha512;

#endif
