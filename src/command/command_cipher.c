/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cipher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 10:11:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/09 12:00:46 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_init(t_cipher_data *data, t_cipher_args *args, int ac, char **av)
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
	return (1);
}

static int	do_free(t_cipher_data *data, int ret)
{
	free(data->buff);
	return (ret);
}

int			command_cipher(int ac, char **av, t_cipher_data *data)
{
	t_cipher_args	args;

	data->cipher.callback = (t_cipher_cb)cmd_cipher_callback;
	data->cipher.userptr = data;
	if (!do_init(data, &args, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_cipher_parse_args(data, &args)
			|| !cmd_cipher_handle_key(data, &args)
			|| !cmd_cipher_handle_iv(data, &args))
		return (do_free(data, EXIT_FAILURE));
	if (!cipher_init(&data->cipher, data->key, data->iv))
	{
		ft_putendl_fd("ft_ssl: cipher init failed\n", 2);
		return (do_free(data, EXIT_FAILURE));
	}
	if (!cmd_cipher_do_execute(data))
		return (do_free(data, EXIT_FAILURE));
	return (do_free(data, EXIT_SUCCESS));
}
