/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adler32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:31:24 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 17:25:46 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/adler32.h"
#include "libft.h"

t_hash		g_hash_adler32 = {(t_hash_init)&adler32_init
		, (t_hash_update)&adler32_update, (t_hash_final)&adler32_final
		, 4, 1, sizeof(t_adler32_ctx), "ADLER32"};

int		adler32_init(t_adler32_ctx *ctx)
{
	ctx->v1 = 1;
	ctx->v2 = 0;
	return (1);
}

int		adler32_update(t_adler32_ctx *ctx, const uint8_t *data, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ctx->v1 += data[i];
		ctx->v2 += ctx->v1;
		++i;
	}
	return (1);
}

int		adler32_final(uint8_t *md, t_adler32_ctx *ctx)
{
	*(uint32_t*)md = ft_swap_uint((ctx->v2 << 16) | ctx->v1);
	return (1);
}
