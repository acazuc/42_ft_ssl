/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_common1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 21:17:17 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/03 21:38:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

static int	generate_key2(uint64_t *key, uint64_t salt, char *password)
{
	t_sha512_ctx	hash_ctx;
	t_pbkdf2_ctx	ctx;

	ctx.h.h = &g_hash_sha512;
	ctx.h.ctx = &hash_ctx;
	ctx.salt = (uint8_t*)&salt;
	ctx.salt_len = 8;
	ctx.password = (uint8_t*)password;
	ctx.password_len = ft_strlen(password);
	ctx.iterations = 4096;
	ctx.out = (uint8_t*)key;
	ctx.out_len = 8;
	if (!pbkdf2(&ctx))
		return (0);
	return (1);
}

static int	transform_bin64(uint64_t *bin64, char *str)
{
	int	len;

	ft_memset(bin64, 0, 8);
	len = ft_strlen(str);
	if (len > 16)
		len = 16;
	if (!hex2bin((uint8_t*)bin64, str, len))
		return (0);
	return (1);
}

static char	*ask_password()
{
	char	*pass;
	char	*tmp;

	if (!(tmp = getpass("Enter des password: ")))
		return (NULL);
	if (!(pass = ft_strdup(tmp)))
		return (NULL);
	if (!(tmp = getpass("Verifying - Enter des password: ")))
	{
		free(pass);
		return (NULL);
	}
	if (strcmp(tmp, pass))
	{
		ft_putendl_fd("Password are not the same", 2);
		free(pass);
		return (NULL);
	}
	return (pass);
}

static int	generate_key(uint64_t *key, char *password, char *salt)
{
	uint64_t	tmp;

	if (!password)
	{
		if (!(password = ask_password()))
			return (0);
	}
	else if (!(password = ft_strdup(password)))
		return (0);
	if (!salt)
	{
		if (!random_bytes((uint8_t*)&tmp, 8))
		{
			free(password);
			return (EXIT_FAILURE);
		}
	}
	else if (!transform_bin64(&tmp, salt))
	{
		free(password);
		return (0);
	}
	tmp = generate_key2(key, tmp, password);
	free(password);
	return (tmp);
}

int		cmd_des_handle_key(uint64_t *key64, t_des_args *args)
{
	if (!args->key)
	{
		if (!generate_key(key64, args->password, args->salt))
			return (0);
	}
	else
	{
		if (!transform_bin64(key64, args->key))
			return (0);
	}
	return (1);
}

int		cmd_des_handle_iv(t_des_ctx *ctx, char *iv)
{
	if (!iv)
	{
		if (!random_bytes((uint8_t*)&ctx->iv, 8))
			return (0);
	}
	else
	{
		if (!transform_bin64(&ctx->iv, iv))
			return (0);
	}
	ctx->iv = ft_swap_ulong(ctx->iv);
	return (1);
}
