/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:17:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 14:47:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

static int	pem_read_file_data_callback(t_pem_read_ctx *ctx, uint8_t *data
		, size_t len)
{
	uint8_t	*tmp;

	//TODO handle cipher !
	if (!(tmp = malloc(len + ctx->len)))
		return (0);
	ft_memcpy(tmp, ctx->data, ctx->len);
	ft_memcpy(tmp + ctx->len, data, len);
	free(ctx->data);
	ctx->data = tmp;
	ctx->len += len;
	return (1);
}

int			pem_read_file_data(t_pem_read_ctx *ctx, char *line, int line_len)
{
	t_b64d_ctx	b64_ctx;

	if (!b64d_init(&b64_ctx))
		return (0);
	b64_ctx.callback = (t_b64_callback)pem_read_file_data_callback;
	b64_ctx.userptr = ctx;
	while (line_len > 0)
	{
		if (!ft_strcmp(line, ctx->end_text))
		{
			b64d_final(&b64_ctx);
			return (1);
		}
		if (!b64d_update(&b64_ctx, (uint8_t*)line, line_len))
		{
			b64d_final(&b64_ctx);
			return (0);
		}
		line_len = pem_read_file_line(ctx, line);
	}
	if (line_len == -1)
		return (0);
	return (1);
}

static int	do_clear(t_pem_read_ctx *ctx, int ret)
{
	free(ctx->salt_iv);
	return (ret);
}

int			pem_read_file(t_pem_read_ctx *ctx)
{
	char	line[66];
	int		line_len;

	ctx->data = NULL;
	ctx->salt_iv = NULL;
	ctx->len = 0;
	if (!pem_read_file_check_begin(ctx)
			|| (line_len = pem_read_file_line(ctx, line)) == -1)
		return (do_clear(ctx, 0));
	if (ctx->ciphered && !ft_strcmp(line, "Proc-Type: 4,ENCRYPTED"))
	{
		if ((line_len = pem_read_file_line(ctx, line)) == -1
				|| !pem_read_file_salt_iv(ctx, line, line_len)
				|| (line_len = pem_read_file_line(ctx, line)) == -1
				|| line_len > 1
				|| (line_len = pem_read_file_line(ctx, line)) == -1)
			return (do_clear(ctx, 0));
	}
	if (!line_len || !pem_read_file_data(ctx, line, line_len))
		return (do_clear(ctx, 0));
	return (do_clear(ctx, 1));
}
