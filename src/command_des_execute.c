/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 21:27:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/03 21:34:17 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

int		cmd_des_do_execute(t_des_data *data, uint64_t key)
{
	if (!do_init(data, key))
		return (0);
	if (!do_update(data))
		return (0);
	if (!do_final(data))
		return (0);
	return (1);
}

