/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_div_mod_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:08:40 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/10 13:07:54 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_part1(t_bignum *r, t_bignum *a, uint64_t i)
{
	if (!bignum_lshift1_op(r, r))
		return (0);
	if (bignum_is_bit_set(a, i))
	{
		if (!r->len)
		{
			if (!bignum_resize(r, 1))
				return (0);
			r->data[0] = 0;
		}
		r->data[0] |= 1;
	}
	return (1);
}

static int	do_part2(t_bignum *r, t_bignum *b, t_bignum *q, uint64_t i)
{
	if (bignum_ucmp(r, b) >= 0)
	{
		if (!bignum_sub_op(r, r, b))
			return (0);
		if (!bignum_set_bit(q, i))
			return (0);
	}
	return (1);
}

static int	do_final(t_bignum *r, t_bignum *q, t_bignum *dv, t_bignum *rm)
{
	if (rm)
	{
		bignum_trunc(r);
		bignum_move(rm, r);
	}
	bignum_clear(r);
	if (dv)
	{
		bignum_trunc(q);
		bignum_move(dv, q);
	}
	bignum_clear(q);
	return (1);
}

static int	do_exec(t_bignum *dv, t_bignum *rm, t_bignum *a, t_bignum *b)
{
	t_bignum	r;
	t_bignum	q;
	uint64_t	i;

	bignum_init(&r);
	bignum_init(&q);
	if (!bignum_reserve(&r, a->len + 1))
		return (0);
	ft_memset(r.data, 0, r.len * sizeof(*r.data));
	i = a->len * 8 * sizeof(*a->data) - 1;
	while (1)
	{
		if (!do_part1(&r, a, i) || !do_part2(&r, b, &q, i))
		{
			bignum_clear(&r);
			bignum_clear(&q);
			return (0);
		}
		if (!i)
			break;
		--i;
	}
	return (do_final(&r, &q, dv, rm));
}

int	bignum_div_mod_op(t_bignum *dv, t_bignum *rm, t_bignum *a, t_bignum *b)
{
	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_is_zero(b))
		return (0);
	if (bignum_is_zero(a))
	{
		if (dv)
			bignum_zero(dv);
		if (rm)
			bignum_zero(rm);
		return (1);
	}
	if (bignum_is_one(b))
	{
		if (dv)
		{
			if (!bignum_copy(dv, a))
				return (0);
		}
		if (rm)
			bignum_zero(rm);
		return (1);
	}
	return (do_exec(dv, rm, a, b));
}
