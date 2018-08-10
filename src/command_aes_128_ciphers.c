/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_128_ciphers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:39:27 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 22:43:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_aes_128_ecb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_ecb_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_ecb_postmod;
	data.cipher.nopad = 0;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_cbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_cbc_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_cbc_postmod;
	data.cipher.nopad = 0;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_pcbc(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_pcbc_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_pcbc_postmod;
	data.cipher.nopad = 0;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_cfb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_cfb_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_cfb_postmod;
	data.cipher.nopad = 1;
	return (command_aes_128(ac, av, &data));
}

int	command_aes_128_ofb(int ac, char **av)
{
	t_aes_data	data;

	data.cipher.premod = (t_cipher_mod)&cipher_ofb_premod;
	data.cipher.postmod = (t_cipher_mod)&cipher_ofb_postmod;
	data.cipher.nopad = 1;
	return (command_aes_128(ac, av, &data));
}
