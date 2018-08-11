/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_256.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:39:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:26:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		command_aes_256(int ac, char **av, t_aes_data *data)
{
	t_aes_args	args;

	data->cipher.callback = (t_cipher_cb)&cmd_aes_callback;
	data->cipher.userptr = data;
	data->key_size = 32;
	if (!cmd_aes_init(data, &args, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_aes_parse_args(data, &args) || !cmd_aes_handle_key(data, &args))
	{
		cmd_aes_free(data);
		return (EXIT_FAILURE);
	}
	if (!cipher_init(&data->cipher, &g_cipher_aes256, data->key))
	{
		cmd_aes_free(data);
		ft_putendl_fd("ft_ssl: des init failed\n", 2);
		return (EXIT_FAILURE);
	}
	if (!cmd_aes_handle_iv(data, &args) || !cmd_aes_do_execute(data))
	{
		cmd_aes_free(data);
		return (EXIT_FAILURE);
	}
	cmd_aes_free(data);
	return (EXIT_SUCCESS);
}
