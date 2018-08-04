/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 21:16:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 16:04:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

uint32_t	pem_write_len(uint8_t *data, uint32_t len)
{
	uint64_t	res;
	uint8_t		tmp;

	res = 0;
	if (len < 127)
	{
		data[0] = len;
		return (1);
	}
	tmp = 1;
	if ((len >> 24) & 0xff)
		tmp = 4;
	else if ((len >> 16) & 0xff)
		tmp = 3;
	else if ((len >> 8) & 0xff)
		tmp = 2;
	data[res++] = 0x80 | tmp;
	if (tmp >= 4)
		data[res++] = len >> 24;
	if (tmp >= 3)
		data[res++] = len >> 16;
	if (tmp >= 2)
		data[res++] = len >> 8;
	data[res++] = len;
	return (res);
}
