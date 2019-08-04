/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aria_192.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:38:37 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:38:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"
#include "ft_ssl.h"

int	command_aria_192_ecb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria192_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_192_cbc(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria192_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_192_pcbc(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria192_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_192_cfb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria192_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_aria_192_ofb(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria192_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
