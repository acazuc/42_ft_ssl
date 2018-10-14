/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:17:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/14 09:51:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

static int	do_clear(t_pem_read_ctx *ctx, int ret)
{
	free(ctx->salt_iv);
	return (ret);
}

int			pem_read_file(t_pem_read_ctx *ctx)
{
	char	line[66];
	int		line_len;

	ctx->cipher = NULL;
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
