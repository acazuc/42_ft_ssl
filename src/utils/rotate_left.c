/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:18:18 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:31:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rotate_left28(uint32_t v, uint32_t c)
{
	return ((v << c) | (v >> (28 - c)));
}

uint32_t	rotate_left32(uint32_t v, uint32_t c)
{
	return ((v << c) | (v >> (32 - c)));
}

uint64_t	rotate_left64(uint64_t v, uint64_t c)
{
	return ((v << c) | (v >> (64 - c)));
}

void		rotate_leftn(uint8_t *dst, uint8_t *src, uint64_t c, uint64_t bytes)
{
	int		i;
	int		d;
	int		dm8;
	uint64_t	bits;

	bits = bytes * 8;
	i = 0;
	while ((uint64_t)i < bytes)
	{
		d = (i * 8 + c) % bits;
		dm8 = d % 8;
		dst[i] = (src[d / 8] & (0xff >> dm8)) << dm8;
		d = (d + 8) % bits;
		dm8 = 8 - (d % 8);
		dst[i] |= (src[d / 8] & (0xff << dm8)) >> dm8;
		++i;
	}
}
