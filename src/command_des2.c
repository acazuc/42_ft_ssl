/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:35:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:35:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "ft_ssl.h"

int	command_des2_ecb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des2_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des2_cbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des2_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des2_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des2_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des2_cfb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des2_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des2_ofb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des2_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
