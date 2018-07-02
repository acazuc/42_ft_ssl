/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:29:12 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/01 11:19:23 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include <stdio.h>

static char	g_invtab[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55
			, 56, 57, 58, 59, 60, 61, -1, -1, -1, 0, -1, -1, -1
			, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
			, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1
			, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34
			, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47
			, 48, 49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
			, -1, -1, -1, -1, -1, -1};

static void	assemble(t_b64d_ctx *ctx, uint8_t *tmp, uint8_t *tmplen)
{
	ctx->buff[ctx->buff_len++] = (g_invtab[tmp[0]] << 2) | (g_invtab[tmp[1]] >> 4);
	if (tmp[2] != '=')
		ctx->buff[ctx->buff_len++] = (g_invtab[tmp[1]] << 4) | (g_invtab[tmp[2]] >> 2);
	if (tmp[2] != '=' && tmp[3] != '=')
		ctx->buff[ctx->buff_len++] = (g_invtab[tmp[2]] << 6) | g_invtab[tmp[3]];
	*tmplen = 0;
}

static int	b64d_chunk(t_b64d_ctx *ctx, uint8_t *tmp, uint8_t *tmplen
		, const uint8_t **data, size_t *len)
{
	uint8_t	tmpi;

	if (ft_isspace(**data))
	{
		++(*data);
		--(*len);
		return (1);
	}
	tmpi = **data;
	if (g_invtab[tmpi] == -1)
		return (0);
	--(*len);
	++(*data);
	tmp[(*tmplen)++] = tmpi;
	if (*tmplen == 4)
		assemble(ctx, tmp, tmplen);
	return (1);
}

int		b64d_init(t_b64d_ctx *ctx)
{
	if (!(ctx->buff = malloc(BASE64_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	ctx->tmpin_len = 0;
	return (1);
}

int		b64d_update(t_b64d_ctx *ctx, const uint8_t *data, size_t len)
{
	uint8_t	tmp[4];
	uint8_t	tmplen;
	int	i;

	if (!len)
		return (1);
	ctx->buff_len = 0;
	tmplen = 0;
	i = -1;
	while (++i < ctx->tmpin_len)
		tmp[tmplen++] = ctx->tmpin[ctx->tmpin_len];
	ctx->tmpin_len = 0;
	while (tmplen < 4 && len)
		if (!b64d_chunk(ctx, tmp, &tmplen, &data, &len))
			return (0);
	ctx->tmpin_len = -1;
	while (++ctx->tmpin_len < tmplen)
	{
		ctx->tmpin[ctx->tmpin_len] = tmp[ctx->tmpin_len];
		len--;
		data++;
	}
	if (ctx->buff_len)
		ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
	return (1);
}

int		b64d_final(t_b64d_ctx *ctx)
{
	free(ctx->buff);
	if (ctx->tmpin_len)
		return (0);
	return (1);
}
