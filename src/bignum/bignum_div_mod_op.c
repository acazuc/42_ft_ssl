/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_div_mod_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:08:40 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/17 19:05:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static int	do_part(t_bignum *rq, t_bignum *a, t_bignum *b, uint64_t i)
{
	if (!bignum_lshift1_op(&rq[0], &rq[0]))
		return (0);
	if (bignum_is_bit_set(a, i) && !bignum_set_bit(&rq[0], 0))
			return (0);
	if (bignum_ucmp(&rq[0], b) >= 0)
	{
		if (!bignum_sub_op(&rq[0], &rq[0], b))
			return (0);
		if (!bignum_set_bit(&rq[1], i))
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

static int	do_clear(t_bignum *rq)
{
	bignum_clear(&rq[0]);
	bignum_clear(&rq[1]);
	return (0);
}

static int	do_exec(t_bignum *dv, t_bignum *rm, t_bignum *a, t_bignum *b)
{
	t_bignum	rq[2];
	uint64_t	i;

	bignum_init(&rq[0]);
	bignum_init(&rq[1]);
	if (!bignum_reserve(&rq[0], b->len)
			|| !bignum_reserve(&rq[1], a->len - b->len + 1))
		return (do_clear(rq));
	i = bignum_num_bits(a);
	while (1)
	{
		if (!do_part(rq, a, b, i))
			return (do_clear(rq));
		if (!i)
			break;
		--i;
	}
	return (do_final(&rq[0], &rq[1], dv, rm));
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
