/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rshift1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:38:26 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 13:50:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_rshift1(t_bignum *r, t_bignum *a)
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
	i = a->len - 1;
	while (1)
	{
		tmp = (a->data[i] & 0x1) << 31;
		r->data[i] = (a->data[i] >> 1) | carry;
		carry = tmp;
		if (!i)
			break;
		--i;
	}
	return (1);
}
