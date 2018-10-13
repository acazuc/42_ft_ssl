/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_file2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:19:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 14:29:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int	pem_read_file_check_begin(t_pem_read_ctx *ctx)
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

int	pem_read_file_salt_iv(t_pem_read_ctx *ctx, char *line, int line_len)
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

int	pem_read_file_line(t_pem_read_ctx *ctx, char *data)
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

