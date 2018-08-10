/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:29:12 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 23:52:02 by acazuc           ###   ########.fr       */
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

static void	assemble(t_b64d_ctx *ctx)
{
	ctx->buff[ctx->buff_len++] = (g_invtab[ctx->tmp[0]] << 2) | (g_invtab[ctx->tmp[1]] >> 4);
	if (ctx->tmp[2] != '=')
		ctx->buff[ctx->buff_len++] = (g_invtab[ctx->tmp[1]] << 4) | (g_invtab[ctx->tmp[2]] >> 2);
	if (ctx->tmp[2] != '=' && ctx->tmp[3] != '=')
		ctx->buff[ctx->buff_len++] = (g_invtab[ctx->tmp[2]] << 6) | g_invtab[ctx->tmp[3]];
	ctx->tmp_len = 0;
}

static int	b64d_chunk(t_b64d_ctx *ctx, const uint8_t **data, size_t *len)
{
	if (ft_isspace(**data))
	{
		++(*data);
		--(*len);
		return (1);
	}
	if (g_invtab[**data] == -1)
		return (0);
	ctx->tmp[ctx->tmp_len++] = **data;
	--(*len);
	++(*data);
	if (ctx->tmp_len == 4)
		assemble(ctx);
	return (1);
}

int		b64d_init(t_b64d_ctx *ctx)
{
	if (!(ctx->buff = malloc(BASE64_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	ctx->tmp_len = 0;
	return (1);
}

int		b64d_update(t_b64d_ctx *ctx, const uint8_t *data, size_t len)
{
	if (!len)
		return (1);
	ctx->buff_len = 0;
	while (len)
	{
		if (!b64d_chunk(ctx, &data, &len))
			return (0);
		if (ctx->buff_len >= BASE64_BUFF_LEN - 3)
		{
			ctx->callback(ctx->userptr, ctx->buff, ctx->buff_len);
			ctx->buff_len = 0;
		}
	}
	if (ctx->buff_len)
		ctx->callback(ctx->userptr, ctx->buff, ctx->buff_len);
	return (1);
}

int		b64d_final(t_b64d_ctx *ctx)
{
	free(ctx->buff);
	ft_putstr("tmp_len: ");
	ft_putul(ctx->tmp_len);
	ft_putchar('\n');
	if (ctx->tmp_len)
		return (0);
	return (1);
}
