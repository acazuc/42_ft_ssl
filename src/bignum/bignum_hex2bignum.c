/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_hex2bignum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 23:13:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:43:33 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static int	get_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

static int	do_fill(t_bignum *bignum, char *s, int len)
{
	int	i;

	if (!bignum_grow(bignum, 0))
		return (0);
	i = 0;
	while (i < len)
	{
		if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'f')
				&& (s[i] < 'A' || s[i] > 'F'))
			return (0);
		bignum->data[bignum->len - 1] |= get_val(s[i])
			<< (4 * (len - 1 - i));
		++i;
	}
	return (1);
}

int	bignum_hex2bignum(t_bignum *bignum, char *s)
{
	int	len;
	int	i;

	bignum_zero(bignum);
	bignum->sign = s[0] == '-';
	if (s[0] == '-')
		++s;
	len = ft_strlen(s);
	i = len - 1;
	while (1)
	{
		if (!do_fill(bignum, s + i - 8, 8))
			return (0);
		if (i < 8)
			break;
		i -= 8;
	}
	if (i)
	{
		if (!do_fill(bignum, 0, i))
			return (0);
	}
	bignum_trunc(bignum);
	return (1);
}
