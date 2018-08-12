/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:25:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 12:02:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "ft_ssl.h"

int	command_des1(int ac, char **av, t_des_data *data)
{
	data->cipher.cipher.cipher = &g_cipher_des1;
	data->cipher.key = data->key;
	data->cipher.iv = data->iv;
	return (command_cipher(ac, av, &data->cipher));
}
