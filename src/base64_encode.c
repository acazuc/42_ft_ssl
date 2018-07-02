/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:19:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/01 11:20:20 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include <stdio.h>

static char	alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvw"
	"xyz0123456789+/";

static uint8_t	get_next_val(t_b64e_ctx *ctx, const uint8_t **data, size_t *len)
{
	uint8_t	ret;
	int	i;

	if (ctx->tmpin_len)
	{
		ret = ctx->tmpin[0];
		i = 1;
		while (i < ctx->tmpin_len)
			ctx->tmpin[i - 1] = ctx->tmpin[i];
		ctx->tmpin_len--;
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
	ctx->buff[ctx->buff_len++] = alphabet[vals[0] >> 2];
	ctx->buff[ctx->buff_len++] = alphabet[((vals[0] & 0x3) << 4)
		| (vals[1] >> 4)];
	ctx->buff[ctx->buff_len++] = alphabet[((vals[1] & 0xf) << 2)
		| (vals[2] >> 6)];
	ctx->buff[ctx->buff_len++] = alphabet[vals[2] & 0x3f];
}

int		b64e_init(t_b64e_ctx *ctx)
{
	if (!(ctx->buff = malloc(BASE64_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	ctx->tmpin_len = 0;
	return (1);
}


int		b64e_update(t_b64e_ctx *ctx, const uint8_t *data, size_t len)
{
	if (!len)
		return (1);
	ctx->buff_len = 0;
	while (len + ctx->tmpin_len >= 3)
	{
		b64e_chunk(ctx, &data, &len);
		if (ctx->buff_len >= BASE64_BUFF_LEN - 4)
		{
			ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
			ctx->buff_len = 0;
		}
	}
	while (len)
	{
		ctx->tmpin[ctx->tmpin_len++] = data[0];
		len--;
		data++;
	}
	if (ctx->buff_len)
		ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
	return (1);
}

int		b64e_final(t_b64e_ctx *ctx)
{
	if (!ctx->tmpin_len)
	{
		free(ctx->buff);
		return (1);
	}
	ctx->buff_len = 0;
	if (ctx->tmpin_len == 1)
	{
		ctx->buff[ctx->buff_len++] = alphabet[ctx->tmpin[0] >> 2];
		ctx->buff[ctx->buff_len++] = alphabet[(ctx->tmpin[0] & 0x3) << 4];
		ctx->buff[ctx->buff_len++] = '=';
		ctx->buff[ctx->buff_len++] = '=';
	}
	else
	{
		ctx->buff[ctx->buff_len++] = alphabet[ctx->tmpin[0] >> 2];
		ctx->buff[ctx->buff_len++] = alphabet[((ctx->tmpin[0] & 0x3) << 4)
			| (ctx->tmpin[1] >> 4)];
		ctx->buff[ctx->buff_len++] = alphabet[(ctx->tmpin[1] & 0xf) << 2];
		ctx->buff[ctx->buff_len++] = '=';
	}
	ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
	return (1);
}
