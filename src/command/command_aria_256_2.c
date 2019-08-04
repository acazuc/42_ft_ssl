/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aria_256_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:39:07 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:41:55 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/aria.h"
#include "ft_ssl.h"

int	command_aria_256_ctr(int ac, char **av)
{
	t_aria_data	data;

	data.cipher.cipher.cipher = &g_cipher_aria256_ctr;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
