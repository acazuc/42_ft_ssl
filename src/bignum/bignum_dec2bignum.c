/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_dec2bignum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 15:39:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 17:34:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static int	do_clear(t_bignum *tmp, t_bignum *mul)
{
	bignum_clear(tmp);
	bignum_clear(mul);
	return (0);
}

static int	do_init(t_bignum *tmp, t_bignum *mul)
{
	bignum_init(tmp);
	bignum_init(mul);
	if (!bignum_grow(mul, 10))
		return (0);
	if (!bignum_resize(tmp, 1))
		return (0);
	return (1);
}

int		bignum_dec2bignum(t_bignum *bignum, char *s)
{
	t_bignum	tmp;
	t_bignum	mul;
	int		len;
	int		i;

	if (!do_init(&tmp, &mul))
		return (do_clear(&tmp, &mul));
	bignum_zero(bignum);
	i = s[0] == '-' ? 1 : 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!bignum_mul(bignum, bignum, &mul))
			return (do_clear(&tmp, &mul));
		if (!ft_isdigit(s[i]))
			return (do_clear(&tmp, &mul));
		tmp.data[0] = s[i] - '0';
		if (!bignum_add(bignum, bignum, &tmp))
			return (do_clear(&tmp, &mul));
		++i;
	}
	do_clear(&tmp, &mul);
	bignum->sign = s[0] == '-';
	return (1);
}
