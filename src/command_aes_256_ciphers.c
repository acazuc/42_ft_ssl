/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_256_ciphers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:44:15 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 10:26:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_aes_256_ecb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ecb;
	return (command_aes_256(ac, av, &data));
}

int	command_aes_256_cbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cbc;
	return (command_aes_256(ac, av, &data));
}

int	command_aes_256_pcbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_pcbc;
	return (command_aes_256(ac, av, &data));
}

int	command_aes_256_cfb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cfb;
	return (command_aes_256(ac, av, &data));
}

int	command_aes_256_ofb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ofb;
	return (command_aes_256(ac, av, &data));
}
