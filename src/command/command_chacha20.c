/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_chacha20.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 11:37:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 18:28:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/chacha20.h"
#include "ft_ssl.h"

int		command_chacha20(int ac, char **av)
{
	t_chacha20_data	data;

	data.cipher.cipher.cipher = &g_cipher_chacha20;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
