/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin2hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 14:05:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 14:08:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	bin2char(uint8_t val)
{
	if (val >= 10)
		return ('a' + val - 10);
	return ('0' + val);
}

void	bin2hex(char *dst, const uint8_t *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i * 2 + 0] = bin2char(src[i] >> 4);
		dst[i * 2 + 1] = bin2char(src[i] & 0xf);
		++i;
	}
}
