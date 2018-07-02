/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_cbc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 23:02:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 11:04:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		command_des_cbc(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_cbc_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_cbc_decrypt_init;
	return (command_des(ac, av, &data));
}
