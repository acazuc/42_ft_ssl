/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:25:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 16:30:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"
#include "sha512.h"
#include <fcntl.h>
#include <stdio.h>

static int	file_open(int ac, char **av, int *i, int type)
{
	(*i)++;
	if (*i >= ac)
		return (-1);
	if (type)
		return (open(av[*i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	return (open(av[*i], O_RDONLY));
}

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

static int	handle_iv(t_des_ctx *ctx, char *iv)
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
static int	handle_key(uint64_t *key64, char *key, char *salt, char *password)
{
	if (!key)
	{
		if (!generate_key(key64, password, salt))
			return (0);
	}
	else
	{
		if (!transform_bin64(key64, key))
			return (0);
	}
	return (1);
}

static int	do_init(t_des_data *data, uint64_t key)
{
	key = ft_swap_ulong(key);
	if (data->mode)
	{
		if (data->decrypt_init(&data->ctx, key))
			return (1);
	}
	else
	{
		if (data->encrypt_init(&data->ctx, key))
			return (1);
	}
	ft_putendl_fd("ft_ssl: error while initializing des", 2);
	return (0);
}

static int	do_update(t_des_data *data)
{
	char	buf[4096];
	int	ret;

	while ((ret = read(data->fdin, buf, 4096)) > 0)
	{
		if (data->mode)
			des_decrypt_update(&data->ctx, (uint8_t*)buf, ret);
		else
			des_encrypt_update(&data->ctx, (uint8_t*)buf, ret);
	}
	if (ret == -1)
	{
		ft_putendl_fd("ft_ssl: error while reading input", 2);
		return (0);
	}
	return (1);
}

static int	do_final(t_des_data *data)
{
	if (data->mode)
	{
		if (des_decrypt_final(&data->ctx))
			return (1);
	}
	else
	{
		if (des_encrypt_final(&data->ctx))
			return (1);
	}
	ft_putendl_fd("ft_ssl: error while finalizing des cipher", 2);
	return (0);
}

static void	callback(uint8_t *data, size_t len, void *userptr)
{
	t_des_data	*datas;
	int osef;

	datas = (t_des_data*)userptr;
	osef = write(datas->fdout, data, len);
	(void)osef;
}

int		command_des(int ac, char **av, t_des_data *data)
{
	uint64_t	key64;
	char		*password;
	char		*salt;
	char		*key;
	char		*iv;
	int		i;

	data->ctx.callback = callback;
	data->ctx.userptr = data;
	data->mode = 0;
	password = NULL;
	salt = NULL;
	key = NULL;
	iv = NULL;
	i = 0;
	data->fdin = 0;
	data->fdout = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-e"))
			data->mode = 0;
		else if (!ft_strcmp(av[i], "-d"))
			data->mode = 1;
		else if (!ft_strcmp(av[i], "-a"))
			data->base64 = 1;
		else if (!ft_strcmp(av[i], "-i"))
		{
			if (data->fdin != 0)
				close(data->fdin);
			if ((data->fdin = file_open(ac, av, &i, 0)) == -1)
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-o"))
		{
			if (data->fdout != 1)
				close(data->fdout);
			if ((data->fdout = file_open(ac, av, &i, 1)) == -1)
				return (EXIT_FAILURE);
		}
		else if (!ft_strcmp(av[i], "-k"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected key after -k", 2);
				return (EXIT_FAILURE);
			}
			key = av[i];
		}
		else if (!ft_strcmp(av[i], "-p"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected password after -p", 2);
				return (EXIT_FAILURE);
			}
			password = av[i];
		}
		else if (!ft_strcmp(av[i], "-s"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected salt after -s", 2);
				return (EXIT_FAILURE);
			}
			salt = av[i];
		}
		else if (!ft_strcmp(av[i], "-v"))
		{
			if (++i >= ac)
			{
				ft_putendl_fd("ft_ssl: expected init vector after -v", 2);
				return (EXIT_FAILURE);
			}
			iv = av[i];
		}
		else
		{
			ft_putstr_fd("ft_ssl: invalid parameter: ", 2);
			ft_putendl_fd(av[i], 2);
			return (EXIT_FAILURE);
		}
		++i;
	}
	if (!handle_key(&key64, key, salt, password))
		return (EXIT_FAILURE);
	if (!handle_iv(&data->ctx, iv))
		return (EXIT_FAILURE);
	if (!do_init(data, key64))
		return (EXIT_FAILURE);
	if (!do_update(data))
		return (EXIT_FAILURE);
	if (!do_final(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
