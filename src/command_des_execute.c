/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 21:27:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 17:45:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_init(t_des_data *data, t_des_ctx *ctx, uint64_t key, int mode)
{
	key = ft_swap_ulong(key);
	if (mode)
		return (data->decrypt_init(ctx, key));
	return (data->encrypt_init(ctx, key));
}

static int	do_update(t_des_data *data)
{
	char	buf[4096];
	int	ret;

	while ((ret = read(data->fdin, buf, 4096)) > 0)
	{
		if (data->mode)
			des_decrypt_update(&data->ctx1, (uint8_t*)buf, ret);
		else
			des_encrypt_update(&data->ctx1, (uint8_t*)buf, ret);
	}
	if (ret == -1)
	{
		ft_putendl_fd("ft_ssl: error while reading input", 2);
		return (0);
	}
	return (1);
}

static int	do_final(t_des_ctx *ctx, int mode)
{
	if (mode)
		return (des_decrypt_final(ctx));
	return (des_encrypt_final(ctx));
}

int		cmd_des_do_execute(t_des_data *data)
{
	uint64_t	tmp;

	if (data->mode)
	{
		tmp = data->key1;
		data->key1 = data->key3;
		data->key3 = tmp;
	}
	if (!do_init(data, &data->ctx1, data->key1, data->mode)
			|| (data->des3 && !do_init(data, &data->ctx2, data->key2, !data->mode))
			|| (data->des3 && !do_init(data, &data->ctx3, data->key3, data->mode)))
	{
		ft_putendl_fd("ft_ssl: error while initializing des", 2);
		return (0);
	}
	if (!do_update(data))
		return (0);
	if (!do_final(&data->ctx1, data->mode)
			|| (data->des3 && !do_final(&data->ctx2, !data->mode))
			|| (data->des3 && !do_final(&data->ctx3, data->mode)))
	{
		ft_putendl_fd("ft_ssl: error while finalizing des", 2);
		return (0);
	}
	return (1);
}
