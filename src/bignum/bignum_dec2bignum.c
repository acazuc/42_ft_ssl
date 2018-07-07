/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_dec2bignum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 15:39:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 22:06:15 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

/*static	int	do_part(t_bignum *bignum, char *s, int pos, int len)
{
	char	*tmp;
	int	a;

	if (!(tmp = ft_strsub(s, pos, len)))
		return (0);
	a = ft_atoi(tmp);
	free(tmp);
	if (!bignum_grow_front(bignum, a))
		return (0);
	return (1);
}

int		bignum_dec2bignum(t_bignum *bignum, char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	if (!len)
		return (bignum_grow(bignum, 0));
	i = 0;
	if (len % 9)
	{
		if (!do_part(bignum, s, 0, len % 9))
			return (0);
	}
	i = len % 9;
	while (i < len)
	{
		if (!do_part(bignum, s, i, 9))
			return (0);
		i += 9;
	}
	return (1);
}*/

int		bignum_dec2bignum(t_bignum *bignum, char *s)
{
	t_bignum	*tmp;
	t_bignum	*mul;
	int		len;
	int		i;

	if (!(mul = bignum_new()))
		return (0);
	if (!bignum_grow(mul, 10))
	{
		bignum_free(mul);
		return (0);
	}
	if (!(tmp = bignum_new()))
	{
		bignum_free(mul);
		return (0);
	}
	if (!bignum_resize(tmp, 1))
	{
		bignum_free(mul);
		bignum_free(tmp);
		return (0);
	}
	bignum_zero(bignum);
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (!bignum_mul(bignum, bignum, mul))
		{
			bignum_free(mul);
			bignum_free(tmp);
			return (0);
		}
		tmp->data[0] = s[i] - '0';
		if (!bignum_add(bignum, bignum, tmp))
		{
			bignum_free(mul);
			bignum_free(tmp);
			return (0);
		}
		++i;
	}
	return (1);
}
