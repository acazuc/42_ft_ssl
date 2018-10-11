/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cipher_common1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 17:18:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:35:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha512.h"
#include "pbkdf2.h"
#include "ft_ssl.h"

static int	generate_key2(uint8_t *key, uint32_t key_size, char *password
		, uint8_t *salt)
{
	t_pbkdf2_ctx	pbkdf2_ctx;

	pbkdf2_ctx.h.hash = &g_hash_sha512;
	pbkdf2_ctx.salt = salt;
	pbkdf2_ctx.salt_len = 8;
	pbkdf2_ctx.password = (uint8_t*)password;
	pbkdf2_ctx.password_len = ft_strlen(password);
	pbkdf2_ctx.iterations = 4096;
	pbkdf2_ctx.out = key;
	pbkdf2_ctx.out_len = key_size;
	if (!pbkdf2(&pbkdf2_ctx))
		return (0);
	return (1);
}

static int	generate_key(uint8_t *key, uint32_t key_size, char *password
		, char *salt)
{
	uint8_t	tmp[8];
	int		ret;

	if (!salt)
	{
		if (!random_bytes(tmp, 8))
			return (0);
	}
	else if (!transform_bin(tmp, salt, 8))
		return (0);
	if (!password)
	{
		if (!(password = ask_password_confirm()))
			return (0);
	}
	else if (!(password = ft_strdup(password)))
		return (0);
	ret = generate_key2(key, key_size, password, tmp);
	free(password);
	return (ret);
}

int			cmd_cipher_handle_key(t_cipher_data *data, t_cipher_args *args)
{
	if (!args->key)
	{
		if (!generate_key(data->key, data->cipher.cipher->key_size
					, args->password, args->salt))
		{
			ft_putendl_fd("ft_ssl: Failed to generate password", 2);
			return (0);
		}
		return (1);
	}
	if (!transform_bin(data->key, args->key, data->cipher.cipher->key_size))
	{
		ft_putendl_fd("ft_ssl: Invalid key", 2);
		return (0);
	}
	return (1);
}

int			cmd_cipher_handle_iv(t_cipher_data *data, t_cipher_args *args)
{
	if (!args->iv)
	{
		if (!random_bytes(data->iv, data->cipher.cipher->block_size))
		{
			ft_putendl_fd("ft_ssl: Failed to generate random iv", 2);
			return (0);
		}
		return (1);
	}
	if (!transform_bin(data->iv, args->iv, data->cipher.cipher->block_size))
	{
		ft_putendl_fd("ft_ssl: invalid iv", 2);
		return (0);
	}
	return (1);
}
