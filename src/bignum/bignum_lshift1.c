/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:48:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 13:49:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_lshift1(t_bignum *r, t_bignum *a)
{
	uint64_t	i;
	int		carry;
	int		tmp;

	bignum_trunc(a);
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	if (!bignum_resize(r, a->len))
		return (0);
	carry = 0;
	i = 0;
	while (i < a->len)
	{
		tmp = (a->data[i] & 0x80000000) >> 31;
		r->data[i] = (a->data[i] << 1) | carry;
		carry = tmp;
		++i;
	}
	return (1);
}
