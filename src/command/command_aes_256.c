/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_256.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:34:17 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/09 12:40:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"
#include "ft_ssl.h"

int	command_aes_256_ecb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.cipher = &g_cipher_aes256_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aes_256_cbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.cipher = &g_cipher_aes256_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aes_256_pcbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.cipher = &g_cipher_aes256_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aes_256_cfb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.cipher = &g_cipher_aes256_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aes_256_ofb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.cipher.cipher = &g_cipher_aes256_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
