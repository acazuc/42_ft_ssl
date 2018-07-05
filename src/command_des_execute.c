/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 21:27:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 13:20:37 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

static int	do_init(t_des_ctx *ctx, uint64_t key, int mode)
{
	key = ft_swap_ulong(key);
	if (mode)
		return (des_decrypt_init(ctx, key));
	return (des_encrypt_init(ctx, key));
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

	if (data->des3 && data->mode)
	{
		tmp = data->keys[0];
		data->keys[0] = data->keys[2];
		data->keys[2] = tmp;
	}
	if (!do_init(&data->ctx[0], data->keys[0], data->mode)
			|| (data->des3 && !do_init(&data->ctx[1], data->keys[1], !data->mode))
			|| (data->des3 && !do_init(&data->ctx[2], data->keys[2], data->mode)))
	{
		ft_putendl_fd("ft_ssl: error while initializing des", 2);
		return (0);
	}
	if (!cmd_des_do_update(data))
		return (0);
	if (!do_final(&data->ctx[0], data->mode)
			|| (data->des3 && !do_final(&data->ctx[1], !data->mode))
			|| (data->des3 && !do_final(&data->ctx[2], data->mode)))
	{
		ft_putendl_fd("ft_ssl: error while finalizing des", 2);
		return (0);
	}
	return (1);
}
