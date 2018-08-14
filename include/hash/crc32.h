/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crc32.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 19:56:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 20:14:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRC32_H
# define CRC32_H

# include "hash.h"

typedef struct		s_crc32_ctx
{
	uint32_t	value;
}			t_crc32_ctx;

int	crc32_init(t_crc32_ctx *ctx);
int	crc32_update(t_crc32_ctx *ctx, const uint8_t *data, size_t len);
int	crc32_final(uint8_t *md, t_crc32_ctx *ctx);

extern t_hash		g_hash_crc32;

#endif
