/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_ofb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 21:12:52 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 21:03:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		command_des_ofb(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_ofb_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_ofb_decrypt_init;
	data.ctx.nopad = 1;
	return (command_des(ac, av, &data));
}
