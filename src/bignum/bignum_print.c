/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:58:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 22:12:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static void	fill(uint64_t n, char **out)
{
	if (n > 9)
	{
		fill(n % 10, out);
		fill(n / 10, out);
	}
	else
	{
		**out = '0' + n;
		(*out)--;
	}
}

void	bignum_print_fd(t_bignum *bignum, int fd)
{
	uint64_t	i;
	char		tmp[10];
	char		*tmp2;

	bignum_trunc(bignum);
	ft_putul_fd(!bignum->len ? 0 : bignum->data[bignum->len - 1], fd);
	if (bignum->len < 2)
		return;
	i = bignum->len - 2;
	while (1)
	{
		ft_memset(tmp, '0', 9);
		tmp2 = tmp + 8;
		fill(bignum->data[i], &tmp2);
		tmp[9] = 0;
		ft_putstr_fd(tmp, fd);
		if (!i)
			break;
		--i;
	}
}

void	bignum_print(t_bignum *bignum)
{
	bignum_print_fd(bignum, 1);
}
