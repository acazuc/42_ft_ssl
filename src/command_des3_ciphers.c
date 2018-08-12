/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des3_ciphers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:55:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 10:37:01 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des3_ecb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ecb;
	return (command_des3(ac, av, &data));
}

int	command_des3_cbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cbc;
	return (command_des3(ac, av, &data));
}

int	command_des3_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_pcbc;
	return (command_des3(ac, av, &data));
}

int	command_des3_cfb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cfb;
	return (command_des3(ac, av, &data));
}

int	command_des3_ofb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ofb;
	return (command_des3(ac, av, &data));
}
