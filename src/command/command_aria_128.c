/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aria_128.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:38:02 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:38:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"
#include "ft_ssl.h"

int	command_aria_128_ecb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria128_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_128_cbc(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria128_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_128_pcbc(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria128_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_128_cfb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria128_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_128_ofb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria128_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
