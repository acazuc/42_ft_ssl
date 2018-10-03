/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:58:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/17 17:37:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static int	print(t_bignum *tmp1, t_bignum *tmp2, t_bignum *div, int fd)
{
	char	c;

	tmp1->sign = 0;
	if (!tmp1->len || (tmp1->len == 1 && !tmp1->data[0]))
		return (1);
	if (!bignum_mod(tmp2, tmp1, div))
		return (0);
	c = tmp2->data[0];
	if (tmp1->len > 1 || tmp1->data[0] > 9)
	{
		if (!bignum_div(tmp1, tmp1, div))
			return (0);
		print(tmp1, tmp2, div, fd);
	}
	ft_putchar_fd('0' + c, fd);
	return (1);
}

static int	do_clear(t_bignum *tmp1, t_bignum *tmp2, t_bignum *div)
{
	bignum_clear(tmp1);
	bignum_clear(tmp2);
	bignum_clear(div);
	return (0);
}

static int	do_init(t_bignum *div, t_bignum *tmp1, t_bignum *tmp2)
{
	bignum_init(div);
	bignum_init(tmp1);
	bignum_init(tmp2);
	if (!bignum_grow(div, 10))
		return (0);
	return (1);
}

int		bignum_print_fd(t_bignum *bignum, int fd)
{
	t_bignum	tmp1;
	t_bignum	tmp2;
	t_bignum	div;
	int		ret;

	bignum_trunc(bignum);
	if (bignum->sign)
		ft_putchar_fd('-', fd);
	if (!bignum->len || (bignum->len == 1 && !bignum->data[0]))
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (!do_init(&div, &tmp1, &tmp2))
		return (do_clear(&tmp1, &tmp2, &div));
	if (!bignum_copy(&tmp1, bignum))
		return (do_clear(&tmp1, &tmp2, &div));
	ret = print(&tmp1, &tmp2, &div, fd);
	bignum_clear(&div);
	bignum_clear(&tmp1);
	bignum_clear(&tmp2);
	return (ret);
}

int		bignum_print(t_bignum *bignum)
{
	return (bignum_print_fd(bignum, 1));
}
