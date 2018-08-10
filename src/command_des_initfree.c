/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_initfree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 16:29:40 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 23:55:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	cmd_des_init(t_des_data *data, t_des_args *args, int ac, char **av)
{
	data->buff_len = 1024 * 16;
	if (!(data->buff = malloc(data->buff_len)))
	{
		ft_putendl_fd("ft_ssl: malloc failed", 2);
		return (0);
	}
	data->buff_pos = 0;
	data->base64 = 0;
	data->fdout = 1;
	data->fdin = 0;
	data->cipher.mode = 0;
	args->password = NULL;
	args->salt = NULL;
	args->key = NULL;
	args->iv = NULL;
	args->av = av;
	args->ac = ac;
	args->i = 0;
	cipher_init(&data->cipher, 8);
	return (1);
}

void	cmd_des_free(t_des_data *data)
{
	free(data->buff);
}
