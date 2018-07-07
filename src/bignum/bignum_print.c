/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:58:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 22:32:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

/*static void	fill(uint64_t n, char **out)
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
}*/

static int	print(t_bignum *tmp, t_bignum *div, int fd)
{
	char	c;

	if (!tmp->len || (tmp->len == 1 && !tmp->data[0]))
		return (1);
	c = tmp->data[0] % 10;
	if (tmp->len > 1 || tmp->data[0] > 9)
	{
		if (!(bignum_div(tmp, tmp, div)))
		{
			bignum_free(div);
			bignum_free(tmp);
			return (0);
		}
		print(tmp, div, fd);
	}
	ft_putchar_fd('0' + c, fd);
	return (1);
}

int	bignum_print_fd(t_bignum *bignum, int fd)
{
	t_bignum	*tmp;
	t_bignum	*div;
	int		ret;

	if (!bignum->len || (bignum->len == 1 && !bignum->data[0]))
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (!(div = bignum_new()))
		return (0);
	if (!bignum_grow(div, 10))
	{
		bignum_free(div);
		return (0);
	}
	if (!(tmp = bignum_dup(bignum)))
	{
		bignum_free(div);
		return (0);
	}
	/*while (tmp->len && (tmp->len != 1 || tmp->data[0]))
	{
		ft_putchar_fd('0' + tmp->data[0] % 10, fd);
		if (!(bignum_div(tmp, tmp, div)))
		{
			bignum_free(div);
			bignum_free(tmp);
			return (0);
		}
	}*/
	ret = print(tmp, div, fd);
	bignum_free(div);
	bignum_free(tmp);
	return (ret);
}

int	bignum_print(t_bignum *bignum)
{
	return (bignum_print_fd(bignum, 1));
}
