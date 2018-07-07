/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_dec2bignum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 15:39:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 15:56:56 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static	int	do_part(t_bignum *bignum, char *s, int pos, int len)
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
}
