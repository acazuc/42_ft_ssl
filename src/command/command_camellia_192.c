/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_camellia_192.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:34:41 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:34:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "ft_ssl.h"

int	command_camellia_192_ecb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia192_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_192_cbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia192_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_192_pcbc(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia192_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_192_cfb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia192_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_camellia_192_ofb(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia192_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
