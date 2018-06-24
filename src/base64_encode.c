/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:19:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 13:16:46 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0"
	"123456789+/";

static void	b64e_loop(t_b64e_ctx *ctx, const uint8_t **data, size_t *len
		, char *len_off)
{
	if (ctx->tmp_len)
	{
		ctx->buff[ctx->buff_len++] = alphabet[(((ctx->tmp << (8
		- ctx->tmp_len)) | ((*data)[0] >> ctx->tmp_len)) & 0xfc) >> 2];
		*len_off = (6 - ctx->tmp_len);
		*len -= *len_off;
		ctx->tmp_len = 0;
	}
	else
	{
		ctx->buff[ctx->buff_len++] = alphabet[((((*data)[0] << *len_off)
		| ((*data)[1] >> (8 - *len_off))) & 0xfc) >> 2];
		if ((*len_off += 6) >= 8)
		{
			(*data)++;
			*len_off -= 8;
		}
		*len -= 6;
	}
}

int		b64e_init(t_b64e_ctx *ctx, t_b64e_callback callback
		, void *userptr)
{
	ctx->callback = callback;
	ctx->userptr = userptr;
	if (!(ctx->buff = malloc(BASE64_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	ctx->tmp = 0;
	ctx->tmp_len = 0;
	return (1);
}


int		b64e_update(t_b64e_ctx *ctx, const uint8_t *data, size_t len)
{
	char	len_off;

	if (!len)
		return (1);
	len *= 8;
	len_off = 0;
	ctx->buff_len = 0;
	while (len + ctx->tmp_len > 6)
	{
		b64e_loop(ctx, &data, &len, &len_off);
		if (ctx->buff_len >= BASE64_BUFF_LEN)
		{
			ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
			ctx->buff_len = 0;
		}
	}
	if (ctx->buff_len)
		ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
	ctx->tmp_len = len;
	if (len)
		ctx->tmp = data[0];
	return (1);
}

int		b64e_finish(t_b64e_ctx *ctx)
{
	if (ctx->tmp_len == 0)
	{
		free(ctx->buff);
		return (1);
	}
	ctx->buff_len = 0;
	ctx->buff[ctx->buff_len++] = alphabet[((ctx->tmp << (8 - ctx->tmp_len)) & 0xfc) >> 2];
	ctx->tmp_len = 8 - ctx->tmp_len;
	while ((ctx->tmp_len = (ctx->tmp_len + 6) % 8))
		ctx->buff[ctx->buff_len++] = '=';
	ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
	free(ctx->buff);
	return (1);
}
