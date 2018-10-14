/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_file_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 09:18:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/14 11:00:06 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

static int	pem_read_file_data_callback(t_pem_read_ctx *ctx, uint8_t *data
		, size_t len)
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

static int	do_cipher_init(t_pem_read_ctx *ctx, t_b64d_ctx *b64_ctx)
{
	uint8_t	key[ctx->cipher->key_size];

	if (ctx->salt_iv_len != (int)FT_MAX(8, ctx->cipher->block_size))
		return (0);
	ctx->cipher_ctx.mode = 1;
	ctx->cipher_ctx.callback = (t_cipher_cb)pem_read_file_data_callback;
	ctx->cipher_ctx.userptr = ctx;
	ctx->cipher_ctx.cipher = ctx->cipher;
	if (!ctx->password && !(ctx->password = ask_password()))
		return (0);
	if (!pem_get_key(&ctx->cipher_ctx, key, ctx->salt_iv, ctx->password))
		return (0);
	b64_ctx->callback = (t_b64_callback)cipher_update;
	b64_ctx->userptr = &ctx->cipher_ctx;
	if (!cipher_init(&ctx->cipher_ctx, key, ctx->salt_iv))
		return (0);
	ft_memcpy(ctx->cipher_ctx.mod1, ctx->salt_iv, ctx->cipher->block_size);
	return (1);
}

static int	do_clear(t_pem_read_ctx *ctx, t_b64d_ctx *b64_ctx, int ret)
{
	b64d_final(b64_ctx);
	if (ctx->cipher && !cipher_final(&ctx->cipher_ctx))
		ret = 0;
	return (ret);
}

int			pem_read_file_data(t_pem_read_ctx *ctx, char *line, int line_len)
{
	t_b64d_ctx	b64_ctx;

	b64_ctx.callback = (t_b64_callback)pem_read_file_data_callback;
	b64_ctx.userptr = ctx;
	if (!b64d_init(&b64_ctx) || (ctx->cipher && !do_cipher_init(ctx, &b64_ctx)))
		return (0);
	while (line_len > 0)
	{
		if (!ft_strcmp(line, ctx->end_text))
			return (do_clear(ctx, &b64_ctx, 1));
		if (!b64d_update(&b64_ctx, (uint8_t*)line, line_len))
			return (do_clear(ctx, &b64_ctx, 0));
		line_len = pem_read_file_line(ctx, line);
	}
	return (do_clear(ctx, &b64_ctx, 0));
}
