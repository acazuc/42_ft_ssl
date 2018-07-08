/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_dec2bignum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 15:39:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 17:18:05 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *tmp, t_bignum *mul)
{
	bignum_free(tmp);
	bignum_free(mul);
	return (0);
}

static int	do_init(t_bignum **tmp, t_bignum **mul)
{
	*tmp = NULL;
	*mul = NULL;
	if (!(*mul = bignum_new()))
		return (0);
	if (!bignum_grow(*mul, 10))
		return (0);
	if (!(*tmp = bignum_new()))
		return (0);
	if (!bignum_resize(*tmp, 1))
		return (0);
	return (1);
}

int		bignum_dec2bignum(t_bignum *bignum, char *s)
{
	t_bignum	*tmp;
	t_bignum	*mul;
	int		len;
	int		i;

	if (!do_init(&tmp, &mul))
		return (do_clear(tmp, mul));
	bignum_zero(bignum);
	i = 0;
	if (s[0] == '-')
		++i;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!bignum_mul(bignum, bignum, mul))
			return (do_clear(tmp, mul));
		if (!ft_isdigit(s[i]))
			return (do_clear(tmp, mul));
		tmp->data[0] = s[i] - '0';
		if (!bignum_add(bignum, bignum, tmp))
			return (do_clear(tmp, mul));
		++i;
	}
	bignum->sign = s[0] == '-';
	bignum_trunc(bignum);
	return (1);
}
