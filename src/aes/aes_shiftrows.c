/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes_shiftrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:10:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 22:22:26 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void	aes_shiftrows(uint8_t *block)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	c;
	uint8_t	d;

	a = block[1];
	b = block[3];
	c = block[10];
	d = block[14];
	dst[1]  = block[5];
	dst[5]  = block[9];
	dst[9]  = block[13];
	dst[13] = i;
	dst[3]  = block[15];
	dst[15] = block[11];
	dst[11] = block[7];
	dst[7]  = j;
	dst[10] = block[2];
	dst[2]  = k;
	dst[14] = block[6];
	dst[6] = l;
}
