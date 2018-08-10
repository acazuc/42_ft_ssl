/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 21:16:59 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:00:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int32_t		pem_read_len(uint8_t *data, uint32_t len, uint32_t *result)
{
	if (!len)
		return (-1);
	if (!(data[0] & 0x80))
	{
		*result = data[0];
		return (1);
	}
	if ((data[0] & (~0x80)) >= len || (data[0] & (~0x80)) > 4)
		return (-1);
	result = 0;
	if ((data[0] & (~0x80)) >= 1)
		*result |= data[1] << (8 * ((data[0] & (~0x80)) - 1));
	if ((data[0] & (~0x80)) >= 2)
		*result |= data[2] << (8 * ((data[0] & (~0x80)) - 2));
	if ((data[0] & (~0x80)) >= 3)
		*result |= data[3] << (8 * ((data[0] & (~0x80)) - 3));
	if ((data[0] & (~0x80)) >= 4)
		*result |= data[4] << (8 * ((data[0] & (~0x80)) - 4));
	return ((data[0] & (~0x80)) + 1);
}

uint32_t	pem_len_len(uint32_t len)
{
	if (len < 127)
		return (1);
	if ((len >> 24) & 0xff)
		return (5);
	if ((len >> 16) & 0xff)
		return (4);
	if ((len >> 8) & 0xff)
		return (3);
	return (2);
}

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
