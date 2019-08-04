/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aria_256.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:38:58 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:39:01 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"
#include "ft_ssl.h"

int	command_aria_256_ecb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria256_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_256_cbc(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria256_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_256_pcbc(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria256_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_256_cfb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria256_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_256_ofb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria256_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
