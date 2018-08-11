/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des1_ciphers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:53:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 19:38:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des_ecb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_ecb_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_ecb_postmod;
	data.cipher.nopad = 0;
	return (command_des(ac, av, &data));
}

int	command_des_cbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_cbc_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_cbc_postmod;
	data.cipher.nopad = 0;
	return (command_des(ac, av, &data));
}

int	command_des_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_pcbc_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_pcbc_postmod;
	data.cipher.nopad = 0;
	return (command_des(ac, av, &data));
}

int	command_des_cfb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_cfb_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_cfb_postmod;
	data.cipher.nopad = 1;
	return (command_des(ac, av, &data));
}

int	command_des_ofb(int ac, char **av)
{
	t_des_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_ofb_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_ofb_postmod;
	data.cipher.nopad = 1;
	return (command_des(ac, av, &data));
}
