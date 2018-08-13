/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_camellia_256_ciphers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 20:22:11 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 20:22:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_camellia_256_ecb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ecb;
	return (command_camellia_256(ac, av, &data));
}

int	command_camellia_256_cbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cbc;
	return (command_camellia_256(ac, av, &data));
}

int	command_camellia_256_pcbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_pcbc;
	return (command_camellia_256(ac, av, &data));
}

int	command_camellia_256_cfb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cfb;
	return (command_camellia_256(ac, av, &data));
}

int	command_camellia_256_ofb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ofb;
	return (command_camellia_256(ac, av, &data));
}
