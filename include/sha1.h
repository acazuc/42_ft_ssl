/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 22:19:28 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/23 22:23:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA1_H
# define SHA1_H

typedef struct		s_sha1_ctx
{
	uint32_t	h[5];
	uint32_t	data[16];
	uint32_t	data_len;
	uint64_t	total_len;
}			t_sha1_ctx;

int	sha1_init(t_sha1_ctx *ctx);
int	sha1_update(t_sha1_ctx *ctx, const uint8_t *data, size_t len);
int	sha1_final(uint8_t *md, t_sha1_ctx *ctx);

#endif
