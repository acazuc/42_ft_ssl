/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift1_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:53:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 22:34:46 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_lshift1_op(t_bignum *r, t_bignum *a)
{
	uint32_t	carry;
	uint32_t	tmp;
	uint64_t	i;

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
	if (carry)
	{
		if (!bignum_resize(r, r->len + 1))
			return (0);
		r->data[i] = carry;
	}
	return (1);
}
