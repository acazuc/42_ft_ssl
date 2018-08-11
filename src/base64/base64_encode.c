/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:19:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 18:25:02 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "libft.h"

static char	g_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvw"
	"xyz0123456789+/";

static uint8_t	get_next_val(t_b64e_ctx *ctx, const uint8_t **data, size_t *len)
{
	uint8_t	ret;
	int	i;

	if (ctx->tmp_len)
	{
		ret = ctx->tmp[0];
		i = 0;
		while (++i < ctx->tmp_len)
			ctx->tmp[i - 1] = ctx->tmp[i];
		ctx->tmp_len--;
		return (ret);
	}
	ret = **data;
	(*data)++;
	(*len)--;
	return (ret);
}

static void	b64e_chunk(t_b64e_ctx *ctx, const uint8_t **data, size_t *len)
{
	uint8_t	vals[3];

	vals[0] = get_next_val(ctx, data, len);
	vals[1] = get_next_val(ctx, data, len);
	vals[2] = get_next_val(ctx, data, len);
	ctx->buff[ctx->buff_len++] = g_alphabet[vals[0] >> 2];
	ctx->buff[ctx->buff_len++] = g_alphabet[((vals[0] & 0x3) << 4)
		| (vals[1] >> 4)];
	ctx->buff[ctx->buff_len++] = g_alphabet[((vals[1] & 0xf) << 2)
		| (vals[2] >> 6)];
	ctx->buff[ctx->buff_len++] = g_alphabet[vals[2] & 0x3f];
}

int		b64e_init(t_b64e_ctx *ctx)
{
	if (!(ctx->buff = malloc(BASE64_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	ctx->buff_len = 0;
	ctx->tmp_len = 0;
	return (1);
}


int		b64e_update(t_b64e_ctx *ctx, const uint8_t *data, size_t len)
{
	if (!len)
		return (1);
	ctx->buff_len = 0;
	while (len + ctx->tmp_len >= 3)
	{
		b64e_chunk(ctx, &data, &len);
		if (ctx->buff_len >= BASE64_BUFF_LEN - 4)
		{
			ctx->callback(ctx->userptr, ctx->buff, ctx->buff_len);
			ctx->buff_len = 0;
		}
	}
	ft_memcpy(ctx->tmp + ctx->tmp_len, data, len);
	ctx->tmp_len += len;
	if (ctx->buff_len)
		ctx->callback(ctx->userptr, ctx->buff, ctx->buff_len);
	return (1);
}

int		b64e_final(t_b64e_ctx *ctx)
{
	if (!ctx->tmp_len)
	{
		free(ctx->buff);
		return (1);
	}
	ctx->buff_len = 0;
	if (ctx->tmp_len == 1)
	{
		ctx->buff[ctx->buff_len++] = g_alphabet[ctx->tmp[0] >> 2];
		ctx->buff[ctx->buff_len++] = g_alphabet[(ctx->tmp[0] & 0x3) << 4];
		ctx->buff[ctx->buff_len++] = '=';
		ctx->buff[ctx->buff_len++] = '=';
	}
	else
	{
		ctx->buff[ctx->buff_len++] = g_alphabet[ctx->tmp[0] >> 2];
		ctx->buff[ctx->buff_len++] = g_alphabet[((ctx->tmp[0] & 0x3) << 4)
			| (ctx->tmp[1] >> 4)];
		ctx->buff[ctx->buff_len++] = g_alphabet[(ctx->tmp[1] & 0xf) << 2];
		ctx->buff[ctx->buff_len++] = '=';
	}
	ctx->callback(ctx->userptr, ctx->buff, ctx->buff_len);
	free(ctx->buff);
	return (1);
}
