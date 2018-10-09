/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_print_rsa_priv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:36:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/09 13:56:20 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"
#include "hash/sha512.h"
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

static void	do_write_salt_iv(t_cipher *cipher, uint8_t *salt_iv, int fd)
{
	char	salt_iv_text[FT_MAX(17, cipher->block_size * 2 + 1)];

	bin2hex(salt_iv_text, salt_iv, cipher->block_size);
	salt_iv_text[FT_MAX(16, cipher->block_size * 2)] = 0;
	ft_putendl_fd("Proc-Type: 4,ENCRYPTED", fd);
	ft_putstr_fd("DEK-Info: ", fd);
	ft_putstr_fd(cipher->name, fd);
	ft_putchar_fd(',', fd);
	ft_putstr_fd(salt_iv_text, fd);
	ft_putstr_fd("\n\n", fd);
}

static int	get_key(t_cipher_ctx *ctx, uint8_t *key, uint8_t *salt_iv
		, char *password)
{
	t_pbkdf2_ctx	pbkdf2_ctx;

	pbkdf2_ctx.h.hash = &g_hash_sha512;
	pbkdf2_ctx.salt = salt_iv;
	pbkdf2_ctx.salt_len = FT_MAX(8, ctx->cipher->block_size);
	pbkdf2_ctx.password = (uint8_t*)password;
	pbkdf2_ctx.password_len = ft_strlen(password);
	pbkdf2_ctx.iterations = 4096;
	pbkdf2_ctx.out = key;
	pbkdf2_ctx.out_len = ctx->cipher->key_size;
	if (!pbkdf2(&pbkdf2_ctx))
		return (0);
	return (1);
}

static int	do_print_ciphered(t_b64_write_ctx *ctx, uint8_t *data, int len
		, t_cipher *cipher)
{
	t_cipher_ctx	cipher_ctx;
	uint8_t			salt_iv[FT_MAX(8, cipher->block_size)];
	char			*password;
	uint8_t			key[cipher->key_size];

	if (!(cipher_ctx.cipher = cipher))
	{
		ft_putendl_fd("ft_ssl: invalid cipher", 2);
		return (0);
	}
	if (!(password = ask_password())
		|| !random_bytes(salt_iv, FT_MAX(8, cipher->block_size))
		|| !get_key(&cipher_ctx, key, salt_iv, password))
		return (0);
	do_write_salt_iv(cipher_ctx.cipher, salt_iv, ctx->fdout);
	cipher_ctx.mode = 0;
	cipher_ctx.callback = (t_cipher_cb)base64_write_update;
	cipher_ctx.userptr = ctx;
	if (!cipher_init(&cipher_ctx, key, salt_iv))
	{
		ft_putendl_fd("ft_ssl: cipher failed", 2);
		return (0);
	}
	ft_memcpy(cipher_ctx.mod1, salt_iv, cipher_ctx.cipher->block_size);
	return (do_cipher(&cipher_ctx, data, len));
}

static int	do_init(t_b64_write_ctx *b64_ctx, t_rsa_ctx *ctx, char **data
		, int *len)
{
	if (!base64_write_init(b64_ctx))
	{
		ft_putendl_fd("ft_ssl: failed to init b64 ctx", 2);
		return (0);
	}
	if ((*len = pem_write_rsa_priv(data, ctx)) == -1)
	{
		ft_putendl_fd("ft_ssl: failed to generate pem file", 2);
		return (0);
	}
	return (1);
}

int			pem_print_rsa_priv(t_rsa_ctx *ctx, int fd, char *cipher_name)
{
	t_b64_write_ctx	b64_ctx;
	char			*data;
	int				len;

	b64_ctx.fdout = fd;
	if (!do_init(&b64_ctx, ctx, &data, &len))
		return (0);
	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", fd);
	if ((cipher_name && !do_print_ciphered(&b64_ctx, (uint8_t*)data, len
					, cipher_get(cipher_name)))
			|| (!cipher_name && !base64_write_update(&b64_ctx, (uint8_t*)data
					, len)))
	{
		free(data);
		return (0);
	}
	base64_write_final(&b64_ctx);
	ft_putendl_fd("-----END RSA PRIVATE KEY-----", fd);
	free(data);
	return (1);
}
