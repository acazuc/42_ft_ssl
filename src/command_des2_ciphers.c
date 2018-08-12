/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2_ciphers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:11:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 10:36:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des2_ecb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ecb;
	return (command_des2(ac, av, &data));
}

int	command_des2_cbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cbc;
	return (command_des2(ac, av, &data));
}

int	command_des2_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_pcbc;
	return (command_des2(ac, av, &data));
}

int	command_des2_cfb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cfb;
	return (command_des2(ac, av, &data));
}

int	command_des2_ofb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ofb;
	return (command_des2(ac, av, &data));
}
