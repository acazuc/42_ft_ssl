/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_128_ciphers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:39:27 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 22:35:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_aes_128_ecb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.mod = &g_cipher_mod_ecb;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_cbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.mod = &g_cipher_mod_cbc;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_pcbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.mod = &g_cipher_mod_pcbc;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_cfb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.mod = &g_cipher_mod_cfb;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_ofb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.mod = &g_cipher_mod_ofb;
	return (command_aes_128(ac, av, &data));
}
