/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:19:14 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 17:40:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	push_data(t_b64_write_ctx *ctx, uint8_t *data, size_t len)
{
	size_t	tmp;
	int	osef;

	while (ctx->buff_pos + len >= ctx->buff_len)
	{
		tmp = ctx->buff_len - ctx->buff_pos;
		ft_memcpy(ctx->buff + ctx->buff_pos, data, tmp);
		data += tmp;
		len -= tmp;
		osef = write(ctx->fdout, ctx->buff, ctx->buff_len);
		ctx->buff_pos = 0;
	}
	ft_memcpy(ctx->buff + ctx->buff_pos, data, len);
	ctx->buff_pos += len;
	(void)osef;
}

static void	b64_callback(t_b64_write_ctx *ctx, uint8_t *data, size_t len)
{
	int		tmp;
	char		nl;

	while (ctx->count + len >= 64)
	{
		tmp = 64 - ctx->count;
		if (tmp > 64)
			tmp = 64;
		push_data(ctx, data, tmp);
		data += tmp;
		len -= tmp;
		ctx->count = 0;
		nl = '\n';
		push_data(ctx, (uint8_t*)&nl, 1);
	}
	ctx->count += len;
	push_data(ctx, data, len);
}

int	base64_write_init(t_b64_write_ctx *ctx)
{
	ctx->count = 0;
	ctx->buff_pos = 0;
	ctx->buff_len = 1024;
	if (!(ctx->buff = malloc(1024)))
		return (0);
	if (!b64e_init(&ctx->b64e_ctx))
	{
		free(ctx->buff);
		return (0);
	}
	ctx->b64e_ctx.callback = (t_b64_callback)b64_callback;
	ctx->b64e_ctx.userptr = ctx;
	return (1);
}

int	base64_write_update(t_b64_write_ctx *ctx, uint8_t *data, size_t len)
{
	return (b64e_update(&ctx->b64e_ctx, data, len));
}

int	base64_write_final(t_b64_write_ctx *ctx)
{
	int	res;
	int	osef;

	res = b64e_final(&ctx->b64e_ctx);
	if (ctx->buff_pos)
		osef = write(ctx->fdout, ctx->buff, ctx->buff_pos);
	if (ctx->count)
		ft_putchar_fd('\n', ctx->fdout);
	free(ctx->buff);
	(void)osef;
	return (res);
}
