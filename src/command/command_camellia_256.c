/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_camellia_256.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:34:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:34:53 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "ft_ssl.h"

int	command_camellia_256_ecb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia256_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_256_cbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia256_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_256_pcbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia256_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_256_cfb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia256_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_256_ofb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia256_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
