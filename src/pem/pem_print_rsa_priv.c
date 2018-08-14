/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_print_rsa_priv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:36:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 19:55:17 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "ft_ssl.h"
#include "libft.h"
#include "pem.h"

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

static int	do_print_ciphered(t_b64_write_ctx *ctx, uint8_t *data, int len, t_cipher *cipher)
{
	t_cipher_ctx	cipher_ctx;
	uint8_t		*key;
	uint8_t		*iv;
	char		iv_text[17];

	ft_putendl_fd("Proc-Type: 4,ENCRYPTED", ctx->fdout);
	ft_putstr_fd("DEK-Info: ", ctx->fdout);
	ft_putstr_fd(cipher->name, ctx->fdout);
	key = (uint8_t*)"0123456789abcdef";//TODO
	iv = (uint8_t*)"0123456789abcdef";//TODO
	bin2hex(iv_text, iv, 8);
	iv_text[16] = 0;
	ft_putchar_fd(',', ctx->fdout);
	ft_putendl_fd(iv_text, ctx->fdout);
	ft_putchar_fd('\n', ctx->fdout);
	cipher_ctx.mode = 0;
	cipher_ctx.cipher = cipher;
	cipher_ctx.callback = (t_cipher_cb)&base64_write_update;
	cipher_ctx.userptr = ctx;
	if (!cipher_init(&cipher_ctx, key, iv))
	{
		ft_putendl_fd("ft_ssl: cipher failed", 2);
		return (0);
	}
	ft_memcpy(cipher_ctx.mod1, iv, cipher->block_size);
	return (do_cipher(&cipher_ctx, data, len));
}

int	pem_print_rsa_priv(t_rsa_ctx *ctx, int fd, char *cipher_name)
{
	t_b64_write_ctx	b64_ctx;
	t_cipher	*cipher;
	char		*data;
	int		len;

	b64_ctx.fdout = fd;
	if (cipher_name)
	{
		if (!(cipher = cipher_get(cipher_name)))
			return (0);
	}
	else
		cipher = NULL;
	if (!base64_write_init(&b64_ctx))
	{
		ft_putendl_fd("ft_ssl: failed to init b64 ctx", 2);
		return (0);
	}
	if ((len = pem_write_rsa_priv(&data, ctx)) == -1)
	{
		ft_putendl_fd("ft_ssl: failed to generate pem file", 2);
		return (0);
	}
	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", fd);
	if ((cipher && !do_print_ciphered(&b64_ctx, (uint8_t*)data, len, cipher))
			|| (!cipher && !base64_write_update(&b64_ctx, (uint8_t*)data, len)))
	{
		free(data);
		return (0);
	}
	base64_write_final(&b64_ctx);
	ft_putendl_fd("-----END RSA PRIVATE KEY-----", fd);
	free(data);
	return (1);
}
