/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cipher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 10:11:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 13:44:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_cipher(int ac, char **av, t_cipher_data *data)
{
	t_cipher_args	args;

	data->cipher.callback = (t_cipher_cb)&cmd_cipher_callback;
	data->cipher.userptr = data;
	if (!cmd_cipher_init(data, &args, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_cipher_parse_args(data, &args) || !cmd_cipher_handle_key(data, &args)
			|| !cmd_cipher_handle_iv(data, &args))
	{
		cmd_cipher_free(data);
		return (EXIT_FAILURE);
	}
	if (!cipher_init(&data->cipher, data->key, data->iv))
	{
		cmd_cipher_free(data);
		ft_putendl_fd("ft_ssl: cipher init failed\n", 2);
		return (EXIT_FAILURE);
	}
	if (!cmd_cipher_do_execute(data))
	{
		cmd_cipher_free(data);
		return (EXIT_FAILURE);
	}
	cmd_cipher_free(data);
	return (EXIT_SUCCESS);
}
