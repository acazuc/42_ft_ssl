/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rc4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 11:37:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 14:29:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/rc4.h"
#include "ft_ssl.h"

int		command_rc4(int ac, char **av)
{
	t_rc4_data	data;

	data.cipher.cipher.cipher = &g_cipher_rc4;
	data.cipher.cipher.mod = &g_cipher_mod_ecb_nopad;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
