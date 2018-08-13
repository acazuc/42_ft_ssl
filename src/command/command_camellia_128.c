/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_camellia_128.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:34:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:34:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "ft_ssl.h"

int	command_camellia_128_ecb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia128_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_128_cbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia128_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_128_pcbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia128_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_128_cfb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia128_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_128_ofb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia128_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
