/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camellia_fl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:43:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 12:05:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "ft_ssl.h"

uint64_t	camellia_fl(uint64_t in1, uint64_t in2)
{
	uint32_t	x1;
	uint32_t	x2;

	x1 = in1 >> 32;
	x2 = in1;
	x2 ^= rotate_left32(x1 & (uint32_t)(in2 >> 32), 1);
	x1 ^= (x2 | (uint32_t)(in2));
	return (((uint64_t)x1 << 32) | x2);
}

uint64_t	camellia_flinv(uint64_t in1, uint64_t in2)
{
	uint32_t	y1;
	uint32_t	y2;

	y1 = in1 >> 32;
	y2 = in1;
	y1 = y1 ^ (y2 | (uint32_t)(in2));
	y2 = y2 ^ rotate_left32(y1 & (uint32_t)(in2 >> 32), 1);
	return (((uint64_t)y1 << 32) | y2);
}
