/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_printhex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 23:15:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 20:30:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static void	print_char(uint8_t c, int fd)
{
	if (c >= 10)
		ft_putchar_fd('a' + c - 10, fd);
	else
		ft_putchar_fd('0' + c, fd);
}

static void	print_hex(t_bignum_word data, int fd, int first)
{
	uint32_t	i;
	uint8_t		v;

	i = 0;
	while (i < 8 * sizeof(t_bignum_word))
	{
		v = (data >> (sizeof(t_bignum_word) * 8 - 4 - i)) & 0xf;
		if (v || !first)
		{
			first = 0;
			print_char(v, fd);
		}
		i += 4;
	}
}

static int	do_test_0(t_bignum *bignum, int fd)
{
	if (!bignum->len || (bignum->len == 1 && !bignum->data[0]))
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	return (0);
}

int		bignum_printhex_fd(t_bignum *bignum, int fd)
{
	uint32_t	i;

	if (do_test_0(bignum, fd))
		return (1);
	if (bignum->sign)
		ft_putchar_fd('-', fd);
	if (!bignum->len)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	i = bignum->len - 1;
	while (1)
	{
		print_hex(bignum->data[i], fd, i == bignum->len - 1);
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
