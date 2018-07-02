/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_cfb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 21:12:48 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 11:04:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		command_des_cfb(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_cfb_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_cfb_decrypt_init;
	return (command_des(ac, av, &data));
}
