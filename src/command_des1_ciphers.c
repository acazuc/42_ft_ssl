/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des1_ciphers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:53:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:38:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des1_ecb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.mod = &g_cipher_mod_ecb;
	return (command_des1(ac, av, &data));
}

int	command_des1_cbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.mod = &g_cipher_mod_cbc;
	return (command_des1(ac, av, &data));
}

int	command_des1_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.mod = &g_cipher_mod_pcbc;
	return (command_des1(ac, av, &data));
}

int	command_des1_cfb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.mod = &g_cipher_mod_cfb;
	return (command_des1(ac, av, &data));
}

int	command_des1_ofb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.mod = &g_cipher_mod_ofb;
	return (command_des1(ac, av, &data));
}
