/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des3_ciphers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:55:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 22:06:10 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des3_ecb(int ac, char **av)
{
	t_des_data	data;

	data.premod = (t_des_mod)&des_ecb_premod;
	data.postmod = (t_des_mod)&des_ecb_postmod;
	data.nopad = 0;
	return (command_des3(ac, av, &data));
}

int	command_des3_cbc(int ac, char **av)
{
	t_des_data	data;

	data.premod = (t_des_mod)&des_cbc_premod;
	data.postmod = (t_des_mod)&des_cbc_postmod;
	data.nopad = 0;
	return (command_des3(ac, av, &data));
}

int	command_des3_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.premod = (t_des_mod)&des_pcbc_premod;
	data.postmod = (t_des_mod)&des_pcbc_postmod;
	data.nopad = 0;
	return (command_des3(ac, av, &data));
}

int	command_des3_cfb(int ac, char **av)
{
	t_des_data	data;

	data.premod = (t_des_mod)&des_cfb_premod;
	data.postmod = (t_des_mod)&des_cfb_postmod;
	data.nopad = 1;
	return (command_des3(ac, av, &data));
}

int	command_des3_ofb(int ac, char **av)
{
	t_des_data	data;

	data.premod = (t_des_mod)&des_ofb_premod;
	data.postmod = (t_des_mod)&des_ofb_postmod;
	data.nopad = 1;
	return (command_des3(ac, av, &data));
}
