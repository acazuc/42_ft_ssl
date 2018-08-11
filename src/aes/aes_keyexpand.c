/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes_keyexpand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:24:26 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 16:15:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"
#include "ft_ssl.h"

static void	expand_core(uint8_t *data, uint8_t i)
{
	*(uint32_t*)data = rotate_right32(*(uint32_t*)data, 8);
	data[0] = aes_subbyte(data[0]);
	data[1] = aes_subbyte(data[1]);
	data[2] = aes_subbyte(data[2]);
	data[3] = aes_subbyte(data[3]);
        data[0] ^= aes_rcon(i);
}

void	aes_keyexpand(t_aes_ctx *ctx, uint8_t *key, uint8_t len)
{
	uint8_t	tmp[4];
	uint8_t	c;
	uint8_t	i;
	uint8_t	j;

	ft_memcpy(ctx->keys[0], key, 16);
	ft_memcpy(ctx->keys[1], key + 16, len - 16);
	c = len;
	i = 1;
	while (c < 240)
	{
		j = 0;
		while (j < 4)
		{
			tmp[j] = ctx->keys[(c + j - 4) / 16][(c + j - 4) % 16];
			++j;
		}
		if (c % len == 0)
		{
			expand_core(tmp, i);
			i++;
		}
		j = 0;
		while (j < 4)
		{
			ctx->keys[c / 16][c % 16] = ctx->keys[(c - len) / 16][(c - len) % 16] ^ tmp[j];
			c++;
			++j;
		}
	}
}
