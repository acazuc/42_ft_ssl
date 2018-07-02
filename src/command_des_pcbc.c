/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_pcbc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 21:12:55 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 21:16:32 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		command_des_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_pcbc_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_pcbc_decrypt_init;
	data.ctx.nopad = 0;
	return (command_des(ac, av, &data));
}
