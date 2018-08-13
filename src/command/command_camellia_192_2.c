/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_camellia_192_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 21:42:52 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 21:43:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "ft_ssl.h"

int	command_camellia_192_ctr(int ac, char **av)
{
	t_camellia_data	data;

	data.cipher.cipher.cipher = &g_cipher_camellia192_ctr;
	data.cipher.key = data.key;
	data.cipher.iv = data.iv;
	return (command_cipher(ac, av, &data.cipher));
}
