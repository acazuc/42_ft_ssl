/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 14:05:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 13:09:40 by acazuc           ###   ########.fr       */
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

int	ishex(char c)
{
	if (c >= 'a' && c <= 'f')
		return (1);
	if (c >= 'A' && c <= 'F')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

uint8_t	char2bin(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (c - '0');
}

int	hex2bin(uint8_t *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len / 2)
	{
		if (!ishex(src[i * 2]) || !ishex(src[i * 2 + 1]))
			return (0);
		dst[i] = (char2bin(src[i * 2]) << 4) | char2bin(src[i * 2 + 1]);
		++i;
	}
	return (1);
}
