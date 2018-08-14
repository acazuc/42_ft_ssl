/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adler32.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:33:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 20:33:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADLER32_H
# define ADLER32_H

# include "hash.h"

typedef struct		s_adler32_ctx
{
	uint16_t	v1;
	uint16_t	v2;
}			t_adler32_ctx;

int	adler32_init(t_adler32_ctx *ctx);
int	adler32_update(t_adler32_ctx *ctx, const uint8_t *data, size_t len);
int	adler32_final(uint8_t *md, t_adler32_ctx *ctx);

extern t_hash		g_hash_adler32;

#endif
