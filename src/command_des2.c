/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:10:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/12 12:02:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/des.h"
#include "ft_ssl.h"

int	command_des2(int ac, char **av, t_des_data *data)
{
	data->cipher.cipher.cipher = &g_cipher_des2;
	data->cipher.key = data->key;
	data->cipher.iv = data->iv;
	return (command_cipher(ac, av, &data->cipher));
}
