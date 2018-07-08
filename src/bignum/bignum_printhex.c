/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_printhex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 23:15:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 14:35:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static void	print_char(uint8_t c, int fd)
{
	if (c >= 10)
		ft_putchar_fd('a' + c - 10, fd);
	else
		ft_putchar_fd('0' + c, fd);
}

static void	print_hex(uint32_t data, int fd)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		print_char((data >> (28 - i)) & 0xf, fd);
		i += 4;
	}
}

int		bignum_printhex_fd(t_bignum *bignum, int fd)
{
	uint64_t	i;

	if (!bignum->len)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	i = bignum->len - 1;
	while (1)
	{
		print_hex(bignum->data[i], fd);
		if (!i)
			break;
		--i;
	}
	return (1);
}

int		bignum_printhex(t_bignum *bignum)
{
	return (bignum_printhex_fd(bignum, 1));
}
