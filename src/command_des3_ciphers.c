/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des3_ciphers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 18:55:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 16:06:13 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des3_ecb(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_ecb_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_ecb_decrypt_init;
	data.ctx1.nopad = 0;
	return (command_des3(ac, av, &data));
}

int	command_des3_cbc(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_cbc_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_cbc_decrypt_init;
	data.ctx1.nopad = 0;
	return (command_des3(ac, av, &data));
}

int	command_des3_pcbc(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_pcbc_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_pcbc_decrypt_init;
	data.ctx1.nopad = 0;
	return (command_des3(ac, av, &data));
}

int	command_des3_cfb(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_cfb_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_cfb_decrypt_init;
	data.ctx1.nopad = 1;
	return (command_des3(ac, av, &data));
}

int	command_des3_ofb(int ac, char **av)
{
	t_des_data	data;

	data.encrypt_init = (t_des_init*)&des_ofb_encrypt_init;
	data.decrypt_init = (t_des_init*)&des_ofb_decrypt_init;
	data.ctx1.nopad = 1;
	return (command_des3(ac, av, &data));
}
