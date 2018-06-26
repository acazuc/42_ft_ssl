/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:47:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:07:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_H
# define SHA384_H

typedef struct		s_sha384_ctx
{
	uint64_t	h[8];
	uint64_t	data[16];
	uint64_t	data_len;
	uint64_t	total_len;
}			t_sha384_ctx;

int	sha384_init(t_sha384_ctx *ctx);
int	sha384_update(t_sha384_ctx *ctx, const uint8_t *data, size_t len);
int	sha384_final(uint8_t *md, t_sha384_ctx *ctx);

extern t_hash		g_hash_sha384;

#endif
