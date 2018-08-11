/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_common1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 17:18:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:53:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha512.h"
#include "ft_ssl.h"

static int	generate_keys2(t_aes_data *data, uint8_t *salt, char *password)
{
	t_pbkdf2_ctx	ctx;
	uint8_t		tmp[32];

	ctx.h.h = &g_hash_sha512;
	ctx.salt = salt;
	ctx.salt_len = 8;
	ctx.password = (uint8_t*)password;
	ctx.password_len = ft_strlen(password);
	ctx.iterations = 4096;
	ctx.out = tmp;
	ctx.out_len = 32;
	if (!pbkdf2(&ctx))
		return (0);
	ft_memcpy(&data->key, tmp, 8);
	return (1);
}

static int	transform_bin(uint8_t *bin, char *str, int max)
{
	int	len;

	ft_memset(bin, 0, max);
	len = ft_strlen(str);
	if (len > max * 2)
		len = max * 2;
	if (!hex2bin(bin, str, len))
		return (0);
	return (1);
}

static char	*ask_password()
{
	char	*pass;
	char	*tmp;

	if (!(tmp = getpass("Enter aes password: ")))
		return (NULL);
	if (!(pass = ft_strdup(tmp)))
		return (NULL);
	if (!(tmp = getpass("Verifying - Enter aes password: ")))
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

static int	generate_keys(t_aes_data *data, char *password, char *salt)
{
	uint8_t	tmp[8];
	int	ret;

	if (!salt)
	{
		if (!random_bytes(tmp, 8))
			return (0);
	}
	else if (!transform_bin(tmp, salt, 8))
		return (0);
	if (!password)
	{
		if (!(password = ask_password()))
			return (0);
	}
	else if (!(password = ft_strdup(password)))
		return (0);
	ret = generate_keys2(data, tmp, password);
	free(password);
	return (ret);
}

int		cmd_aes_handle_key(t_aes_data *data, t_aes_args *args)
{
	if (!args->key)
	{
		if (!generate_keys(data, args->password, args->salt))
		{
			ft_putendl_fd("ft_ssl: Failed to generate password", 2);
			return (0);
		}
	}
	if (!transform_bin(data->key, args->key, data->key_size))
	{
		ft_putendl_fd("ft_ssl: Invalid key", 2);
		return (0);
	}
	return (1);
}

int		cmd_aes_handle_iv(t_aes_data *data, t_aes_args *args)
{
	if (!args->iv)
	{
		if (!random_bytes(data->cipher.iv, 16))
		{
			ft_putendl_fd("ft_ssl: Failed to generate random iv", 2);
			return (0);
		}
	}
	else
	{
		if (!transform_bin(data->cipher.iv, args->iv, 16))
		{
			ft_putendl_fd("ft_ssl: invalid iv", 2);
			return (0);
		}
	}
	return (1);
}
