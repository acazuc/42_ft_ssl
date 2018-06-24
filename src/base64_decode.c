/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:29:12 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 14:00:16 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0"
	"123456789+/";

char	getIndex(char c)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		if (c == alphabet[i])
			return (i);
		++i;
	}
	return (-1);
}

int	b64d_init(t_b64d_ctx *ctx, t_b64d_callback callback, void *userptr)
{
	ctx->callback = callback;
	ctx->userptr = userptr;
	if (!(ctx->buff = malloc(BASE64_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	ctx->tmp = 0;
	ctx->tmp_len = 0;
	return (1);
}

int	b64d_update(t_b64d_ctx *ctx, const uint8_t *data, size_t len)
{
	char	len_off;

	if (!len)
		return (1);
	len *= 6;
	len_off = 0;
	while (ctx->tmp_len + len >= 6)
	{
		if (ft_isspace(data[0]))
		{
			++data;
			len -= len;
			continue;
		}
		if (ctx->tmp_len)
		{
			char p1 = getIndex(ctx->tmp);
			if (p1 == -1)
				return (0);
			char p2 = getIndex(data[0]);
			if (p2 == -1)
				return (0);
			ctx->buff[ctx->buff_len++] = (p1 << (2 + ctx->tmp_len)) | (p2 >> ctx->tmp_len);
			len_off = (8 - ctx->tmp_len);
			len -= len_off;
			ctx->tmp_len = 0;
		}
		else
		{
			char p1 = getIndex(data[0]);
			if (p1 == -1)
				return (0);
			char p2 = getIndex(data[1]);
			if (p2 == -1)
				return (0);
			ctx->buff[ctx->buff_len++] = (p1 << (2 + len_off)) | (p2 >> (4 - len_off));
			if ((len_off += 6) >= 8)
			{
				++data;
				len_off -= 8;
			}
			len -= 8;
		}
	}
	ctx->tmp_len = len;
	if (len)
		ctx->tmp = data[0];
	(void)data;
	return (1);
}

int	b64d_finish(t_b64d_ctx *ctx)
{
	free(ctx->buff);
	return (1);
}
