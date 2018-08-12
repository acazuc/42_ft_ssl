/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_192_ciphers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:43:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 10:25:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_aes_192_ecb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ecb;
	return (command_aes_192(ac, av, &data));
}

int	command_aes_192_cbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cbc;
	return (command_aes_192(ac, av, &data));
}

int	command_aes_192_pcbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_pcbc;
	return (command_aes_192(ac, av, &data));
}

int	command_aes_192_cfb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_cfb;
	return (command_aes_192(ac, av, &data));
}

int	command_aes_192_ofb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.mod = &g_cipher_mod_ofb;
	return (command_aes_192(ac, av, &data));
}
