/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:24:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 11:32:16 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

static void	do_write_salt_iv(t_cipher *cipher, uint8_t *salt_iv, int fd)
{
	char	salt_iv_text[FT_MAX(17, cipher->block_size * 2 + 1)];

	bin2hex(salt_iv_text, salt_iv, cipher->block_size);
	salt_iv_text[FT_MAX(16, cipher->block_size * 2)] = 0;
	ft_putstr_fd("Proc-Type: 4,ENCRYPTED\n", fd);
	ft_putstr_fd("DEK-Info: ", fd);
	ft_putstr_fd(cipher->name, fd);
	ft_putchar_fd(',', fd);
	ft_putstr_fd(salt_iv_text, fd);
	ft_putstr_fd("\n\n", fd);
}

static int	do_cipher(t_cipher_ctx *ctx, uint8_t *data, int len)
{
	if (!cipher_update(ctx, data, len))
	{
		ft_putendl_fd("ft_ssl: cipher failed", 2);
		return (0);
	}
	if (!cipher_final(ctx))
	{
		ft_putendl_fd("ft_ssl: cipher failed", 2);
		return (0);
	}
	return (1);
}

int			pem_print_ciphered(t_pem_write_ctx *ctx)
{
	t_cipher_ctx	cipher_ctx;
	uint8_t			salt_iv[FT_MAX(8, ctx->cipher->block_size)];
	char			*password;
	uint8_t			key[ctx->cipher->key_size];

	cipher_ctx.cipher = ctx->cipher;
	if (!(password = ask_password())
		|| !random_bytes(salt_iv, FT_MAX(8, ctx->cipher->block_size))
		|| !pem_get_key(&cipher_ctx, key, salt_iv, password))
		return (0);
	ft_putendl_fd(ctx->begin_text, ctx->b64_ctx.fdout);
	do_write_salt_iv(cipher_ctx.cipher, salt_iv, ctx->b64_ctx.fdout);
	cipher_ctx.mode = 0;
	cipher_ctx.callback = (t_cipher_cb)base64_write_update;
	cipher_ctx.userptr = ctx;
	if (!cipher_init(&cipher_ctx, key, salt_iv))
	{
		ft_putendl_fd("ft_ssl: cipher failed", 2);
		return (0);
	}
	ft_memcpy(cipher_ctx.mod1, salt_iv, cipher_ctx.cipher->block_size);
	return (do_cipher(&cipher_ctx, (uint8_t*)ctx->data, ctx->len));
}


int			pem_write_init(t_pem_write_ctx *ctx)
{
	if (!base64_write_init(&ctx->b64_ctx))
	{
		ft_putendl_fd("ft_ssl: failed to init b64 ctx", 2);
		return (0);
	}
	if (ctx->ciphered && !ctx->cipher)
	{
		ft_putendl_fd("ft_ssl: invalid cipher", 2);
		return (0);
	}
	return (1);
}

int			pem_write_write(t_pem_write_ctx *ctx)
{
	if (ctx->ciphered)
	{
		if (!pem_print_ciphered(ctx))
			return (0);
	}
	else
	{
		ft_putendl_fd(ctx->begin_text, ctx->b64_ctx.fdout);
		if (!base64_write_update(&ctx->b64_ctx, (uint8_t*)ctx->data, ctx->len))
			return (0);
	}
	return (1);
}

int			pem_write_final(t_pem_write_ctx *ctx)
{
	base64_write_final(&ctx->b64_ctx);
	ft_putendl_fd(ctx->end_text, ctx->b64_ctx.fdout);
	return (1);
}
