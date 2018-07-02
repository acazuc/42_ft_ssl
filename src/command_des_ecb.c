/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_ecb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 23:02:17 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 21:07:26 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		command_des_ecb(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_ecb_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_ecb_decrypt_init;
	data.ctx.nopad = 0;
	return (command_des(ac, av, &data));
}
