/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_camellia_192_ciphers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 20:22:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 20:22:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_camellia_192_ecb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ecb;
	return (command_camellia_192(ac, av, &data));
}

int	command_camellia_192_cbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cbc;
	return (command_camellia_192(ac, av, &data));
}

int	command_camellia_192_pcbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_pcbc;
	return (command_camellia_192(ac, av, &data));
}

int	command_camellia_192_cfb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cfb;
	return (command_camellia_192(ac, av, &data));
}

int	command_camellia_192_ofb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ofb;
	return (command_camellia_192(ac, av, &data));
}
