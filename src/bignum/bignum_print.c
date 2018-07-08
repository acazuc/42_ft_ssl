/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:58:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 19:55:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	print(t_bignum *tmp1, t_bignum *tmp2, t_bignum *div, int fd)
{
	char	c;

	if (!tmp1->len || (tmp1->len == 1 && !tmp1->data[0]))
		return (1);
	if (!bignum_mod(tmp2, tmp1, div))
		return (0);
	c = tmp2->data[0];
	if (tmp1->len > 1 || tmp1->data[0] > 9)
	{
		if (!(bignum_div(tmp1, tmp1, div)))
			return (0);
		print(tmp1, tmp2, div, fd);
	}
	ft_putchar_fd('0' + c, fd);
	return (1);
}

static int	do_clear(t_bignum *tmp1, t_bignum *tmp2, t_bignum *div)
{
	bignum_free(tmp1);
	bignum_free(tmp2);
	bignum_free(div);
	return (0);
}

static int	do_init(t_bignum **div, t_bignum **tmp2)
{
	if (!(*div = bignum_new()))
		return (0);
	if (!bignum_grow(*div, 10))
		return (0);
	if (!(*tmp2 = bignum_new()))
		return (0);
	return (1);
}

int		bignum_print_fd(t_bignum *bignum, int fd)
{
	t_bignum	*tmp1;
	t_bignum	*tmp2;
	t_bignum	*div;
	int		ret;

	if (bignum->sign)
		ft_putchar_fd('-', fd);
	tmp1 = NULL;
	tmp2 = NULL;
	div = NULL;
	if (!bignum->len || (bignum->len == 1 && !bignum->data[0]))
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (!do_init(&div, &tmp2))
		return (do_clear(tmp1, tmp2, div));
	if (!(tmp1 = bignum_dup(bignum)))
		return (do_clear(tmp1, tmp2, div));
	tmp1->sign = 0;
	ret = print(tmp1, tmp2, div, fd);
	bignum_free(div);
	bignum_free(tmp1);
	bignum_free(tmp2);
	return (ret);
}

int		bignum_print(t_bignum *bignum)
{
	return (bignum_print_fd(bignum, 1));
}
