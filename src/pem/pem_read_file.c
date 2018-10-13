/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:17:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 14:15:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int		pem_read_file_check_begin(t_pem_read_ctx *ctx)
{
	int		readed;
	int		begin_len;
	char	*data;

	begin_len = strlen(ctx->begin_text);
	if (!(data = malloc(begin_len + 1)))
		return (0);
	if ((readed = read(ctx->fd, data, begin_len + 1)) != begin_len + 1)
	{
		free(data);
		return (0);
	}
	if (memcmp(data, ctx->begin_text, begin_len))
	{
		free(data);
		return (0);
	}
	if (data[begin_len] != '\n')
	{
		free(data);
		return (0);
	}
	free(data);
	return (1);
}

int		pem_read_file_line(t_pem_read_ctx *ctx, char *data)
{
	int	readed;
	int	i;

	i = 0;
	while (i < 65)
	{
		if ((readed = read(ctx->fd, data, 1)) == -1)
			return (-1);
		if (!readed || *data == '\n')
		{
			*data = '\0';
			return (i);
		}
		++data;
		++i;
	}
	return (-1);
}

int		pem_read_file_check_end(t_pem_read_ctx *ctx)
{
	int		readed;
	int		end_len;
	char	*data;

	end_len = strlen(ctx->end_text);
	if (!(data = malloc(end_len + 2)))
		return (0);
	if ((readed = read(ctx->fd, data, end_len + 2)) != end_len + 1)
	{
		free(data);
		return (0);
	}
	if (memcmp(data, ctx->end_text, end_len))
	{
		free(data);
		return (0);
	}
	if (data[end_len] != '\n')
	{
		free(data);
		return (0);
	}
	free(data);
	return (1);
}

int		pem_read_file_salt_iv(t_pem_read_ctx *ctx, char *line, int line_len)
{
	char	*coma;
	int		iv_len;

	if (line_len < 11)
		return (0);
	if (ft_memcmp(line, "DEK-Info: ", 10))
		return (0);
	line += 10;
	if (!(coma = ft_strchr(line, ',')))
		return (0);
	*coma = '\0';
	if (!(ctx->cipher = cipher_get(line)))
		return (0);
	iv_len = ft_strlen(coma + 1);
	if (!iv_len || iv_len & 1)
		return (0);
	ctx->salt_iv_len = iv_len / 2;
	if (!(ctx->salt_iv = malloc(ctx->salt_iv_len)))
		return (0);
	if (!hex2bin(ctx->salt_iv, coma + 1, ctx->salt_iv_len))
		return (0);
	return (1);
}

static int	pem_read_file_data_callback(t_pem_read_ctx *ctx, uint8_t *data, size_t len)
{
	uint8_t	*tmp;

	if (!(tmp = malloc(len + ctx->len)))
		return (0);
	ft_memcpy(tmp, ctx->data, ctx->len);
	ft_memcpy(tmp + ctx->len, data, len);
	free(ctx->data);
	ctx->data = tmp;
	ctx->len += len;
	return (1);
}

int		pem_read_file_data(t_pem_read_ctx *ctx, char *line, int line_len)
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

int		pem_read_file(t_pem_read_ctx *ctx)
{
	char	line[66];
	int		line_len;

	ctx->data = NULL;
	ctx->salt_iv = NULL;
	ctx->len = 0;
	if (!pem_read_file_check_begin(ctx))
		return (do_clear(ctx, 0));
	if ((line_len = pem_read_file_line(ctx, line)) == -1)
		return (do_clear(ctx, 0));
	if (ctx->ciphered && !ft_strcmp(line, "Proc-Type: 4,ENCRYPTED"))
	{
		if ((line_len = pem_read_file_line(ctx, line)) == -1)
			return (do_clear(ctx, 0));
		if (!pem_read_file_salt_iv(ctx, line, line_len))
			return (do_clear(ctx, 0));
		if ((line_len = pem_read_file_line(ctx, line)) == -1)
			return (do_clear(ctx, 0));
		if (line_len > 1)
			return (do_clear(ctx, 0));
		if ((line_len = pem_read_file_line(ctx, line)) == -1)
			return (do_clear(ctx, 0));
	}
	if (!line_len)
		return (do_clear(ctx, 0));
	if (!pem_read_file_data(ctx, line, line_len))
		return (do_clear(ctx, 0));
	return (do_clear(ctx, 1));
}
