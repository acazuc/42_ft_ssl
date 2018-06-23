/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:54:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/23 19:13:37 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

typedef struct		s_md5_ctx
{
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	data[16];
	uint32_t	data_len;
	uint64_t	total_len;
}			t_md5_ctx;

int	md5_init(t_md5_ctx *ctx);
int	md5_update(t_md5_ctx *ctx, const uint8_t *data, size_t len);
int	md5_final(uint8_t *md, t_md5_ctx *ctx);

# define MD5_FF(B, C, D) (((B) & (C)) | ((~(B)) & (D)))
# define MD5_FG(B, C, D) (((B) & (D)) | ((C) & (~(D))))
# define MD5_FH(B, C, D) ((B) ^ (C) ^ (D))
# define MD5_FI(B, C, D) ((C) ^ ((B) | (~(D))))

#endif
