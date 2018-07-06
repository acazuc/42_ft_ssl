/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:36:11 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 22:59:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_mul(t_bignum *r, t_bignum *a, t_bignum *b)
{
	uint64_t	carry;
	uint64_t	tmp;
	uint64_t	i;
	uint64_t	j;

	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_is_zero(a) || bignum_is_zero(b))
	{
		bignum_zero(r);
		return (1);
	}
	bignum_zero(r);
	if (!(bignum_resize(r, a->len + b->len)))
		return (0);
	ft_memset(r->data, 0, r->len * sizeof(*r->data));
	i = 0;
	while (i < a->len)
	{
		carry = 0;
		j = 0;
		while (j < b->len || carry)
		{
			tmp = (uint64_t)r->data[i + j] + carry
				+ (uint64_t)a->data[i]
				* (j < b->len ? (uint64_t)b->data[j] : 0);
			r->data[i + j] = tmp % BIGNUM_BASE;
			carry = tmp / BIGNUM_BASE;
			++j;
		}
		++i;
	}
	bignum_trunc(r);
	return (1);
}
