/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mul_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:02:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 13:40:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_init(t_bignum *r, t_bignum *a, t_bignum *b, uint64_t *ret)
{
	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_is_zero(a) || bignum_is_zero(b))
	{
		*ret = 1;
		bignum_zero(r);
		return (1);
	}
	if (bignum_is_one(a))
	{
		*ret = bignum_copy(r, b);
		return (1);
	}
	if (bignum_is_one(b))
	{
		*ret = bignum_copy(r, a);
		return (1);
	}
	return (0);
}

static void	do_loop(t_bignum *tmp, t_bignum *a, t_bignum *b, uint64_t i)
{
	uint64_t	carry;
	uint64_t	ai;
	uint64_t	t;
	uint64_t	j;

	carry = 0;
	j = 0;
	ai = a->data[i];
	while (j < b->len)
	{
		t = (uint64_t)tmp->data[i + j] + carry + ai * b->data[j];
		tmp->data[i + j] = t % BIGNUM_BASE;
		carry = t / BIGNUM_BASE;
		++j;
	}
	if (carry)
		tmp->data[i + j] += carry;
}

int		bignum_mul_op(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	*tmp;
	uint64_t	i;

	if (do_init(r, a, b, &i))
		return (i);
	if (!(tmp = bignum_new()))
		return (0);
	if (!bignum_resize(tmp, a->len + b->len))
	{
		bignum_free(tmp);
		return (0);
	}
	ft_memset(tmp->data, 0, (a->len + b->len) * sizeof(*tmp->data));
	i = 0;
	while (i < a->len)
	{
		do_loop(tmp, a, b, i);
		++i;
	}
	bignum_trunc(tmp);
	i = bignum_copy(r, tmp);
	bignum_free(tmp);
	return (i);
}
