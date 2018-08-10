/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes_mixcolumns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:18:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 22:26:16 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void	aes_mixcolumns(uint8_t *block)
{
	uint8_t a[4];
	uint8_t b[4];
	uint8_t tmp;
	uint8_t i;

	i = 0;
	while (i < 4)
	{
		a[i] = r[i];
		tmp = (int8_t)block[i] >> 7;
		b[i] = r[i] << 1;
		b[i] ^= 0x1b & tmp;
		++i;
	}
	block[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
	block[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
	block[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
	block[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}
