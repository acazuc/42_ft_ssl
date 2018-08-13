/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:35:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:35:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "ft_ssl.h"

int	command_des1_ecb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des1_ecb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des1_cbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des1_cbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des1_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des1_pcbc;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des1_cfb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des1_cfb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}

int	command_des1_ofb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.cipher.cipher = &g_cipher_des1_ofb;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
