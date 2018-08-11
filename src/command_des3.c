/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:15:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:16:10 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des3(int ac, char **av, t_des_data *data)
{
	t_des_args	args;

	data->cipher.callback = (t_cipher_cb)&cmd_des_callback;
	data->cipher.userptr = data;
	if (!cmd_des_init(data, &args, ac, av))
		return (EXIT_FAILURE);
	if (!cmd_des_parse_args(data, &args) || !cmd_des_handle_key(data, &args))
	{
		cmd_des_free(data);
		return (EXIT_FAILURE);
	}
	if (!cipher_init(&data->cipher, &g_cipher_des3, data->key))
	{
		cmd_des_free(data);
		ft_putendl_fd("ft_ssl: des init failed\n", 2);
		return (EXIT_FAILURE);
	}
	if (!cmd_des_handle_iv(data, &args) || !cmd_des_do_execute(data))
	{
		cmd_des_free(data);
		return (EXIT_FAILURE);
	}
	cmd_des_free(data);
	return (EXIT_SUCCESS);
}
