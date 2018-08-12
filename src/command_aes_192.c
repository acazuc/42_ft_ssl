/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_192.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:39:06 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 12:01:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aes.h"
#include "ft_ssl.h"

int		command_aes_192(int ac, char **av, t_aes_data *data)
{
	data->cipher.cipher.cipher = &g_cipher_aes192;
	data->cipher.key = data->key;
	data->cipher.iv = data->iv;
	return (command_cipher(ac, av, &data->cipher));
}
