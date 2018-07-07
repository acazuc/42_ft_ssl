/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:36:11 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 19:47:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_mul(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	*tmp;
	uint64_t	carry;
	uint64_t	t;
	uint64_t	i;
	uint64_t	j;

	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_is_zero(a) || bignum_is_zero(b))
	{
		bignum_zero(r);
		return (1);
	}
	if (bignum_is_one(a))
		return (bignum_copy(r, b));
	if (bignum_is_one(b))
		return (bignum_copy(r, a));
	if (!(tmp = bignum_new()))
		return (0);
	if (!(bignum_resize(tmp, a->len + b->len)))
	{
		bignum_free(tmp);
		return (0);
	}
	ft_memset(tmp->data, 0, (a->len + b->len) * sizeof(*tmp->data));
	i = 0;
	while (i < a->len)
	{
		carry = 0;
		j = 0;
		while (j < b->len || carry)
		{
			t = (uint64_t)tmp->data[i + j] + carry
				+ (uint64_t)a->data[i]
				* (j < b->len ? (uint64_t)b->data[j] : 0);
			tmp->data[i + j] = t % BIGNUM_BASE;
			carry = t / BIGNUM_BASE;
			++j;
		}
		++i;
	}
	bignum_trunc(tmp);
	bignum_copy(r, tmp);
	bignum_free(tmp);
	return (1);
}
