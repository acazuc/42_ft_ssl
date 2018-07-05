/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 21:57:19 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 18:06:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	push_data(t_des_data *ctx, uint8_t *data, size_t len)
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

static void	b64_callback(t_des_data *ctx, uint8_t *data, size_t len)
{
	int		tmp;
	char		nl;

	while (ctx->b64_count + len >= 64)
	{
		tmp = 64 - ctx->b64_count;
		if (tmp > 64)
			tmp = 64;
		push_data(ctx, data, tmp);
		data += tmp;
		len -= tmp;
		ctx->b64_count = 0;
		nl = '\n';
		push_data(ctx, (uint8_t*)&nl, 1);
	}
	ctx->b64_count += len;
	push_data(ctx, data, len);
}

int		cmd_des_callback(t_des_data *ctx, uint8_t *data, size_t len)
{
	if (ctx->cipher.mode && ctx->cipher.ended && !ctx->cipher.nopad)
	{
		if (data[7] > 8)
		{
			ft_putendl_fd("ft_ssl: invalid stream end", 2);
			return (0);
		}
		len -= data[7];
	}
	if (!ctx->cipher.mode && ctx->base64)
	{
		ctx->b64e_ctx.callback = (t_b64_callback)&b64_callback;
		ctx->b64e_ctx.userptr = ctx;
		if (!(b64e_update(&ctx->b64e_ctx, data, len)))
		{
			ft_putendl_fd("ft_ssl: base64 encode failed", 2);
			return (0);
		}
		if (ctx->cipher.ended)
		{
			if (!b64e_final(&ctx->b64e_ctx))
			{
				ft_putendl_fd("ft_ssl: base64 encode failed", 2);
				return (0);
			}
		}
	}
	else
		push_data(ctx, data, len);
	if (ctx->cipher.ended)
		len = write(ctx->fdout, ctx->buff, ctx->buff_pos);
	if (ctx->cipher.ended && ctx->b64_count)
		ft_putchar('\n');
	return (1);
}
