/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:54:57 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 20:50:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int		test_simple(t_bignum *r, t_bignum *a, uint32_t n)
{
	bignum_trunc(a);
	if (!n)
	{
		bignum_copy(r, a);
		return (1);
	}
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	return (0);
}

static int		init(t_bignum *tmp, t_bignum *a, uint32_t n, uint32_t *s8)
{
	uint32_t	len;

	*s8 = sizeof(*tmp->data) * 8;
	len = (bignum_num_bits(a) + n + *s8 - 1) / *s8;
	bignum_init(tmp);
	if (!bignum_reserve(tmp, len))
		return (0);
	tmp->len = len;
	return (1);
}

static void		do_shift(t_bignum_word *tmp, t_bignum *a, int32_t *next, uint32_t s8)
{
	int32_t	nms8;

	if (*next > 0)
	{
		nms8 = *next % s8;
		*tmp = (a->data[*next / s8]
				& ((t_bignum_word)(-1) << nms8)) >> nms8;
	}
	else
		*tmp = 0;
	if ((*next += s8) >= (int32_t)a->len * (int32_t)s8)
		return ;
	if (*next > 0)
	{
		nms8 = *next % s8;
		*tmp |= (a->data[*next / s8]
				& ((t_bignum_word)(-1) >> (s8 - nms8))) << (s8 - nms8);
	}
}

int			bignum_lshift_op(t_bignum *r, t_bignum *a, uint32_t n)
{
	t_bignum	tmp;
	int32_t		next;
	uint32_t	i;
	uint32_t	s8;

	if (test_simple(r, a, n))
		return (1);
	if (!init(&tmp, a, n, &s8))
		return (0);
	i = -1;
	while (++i < tmp.len)
	{
		next = i * s8 - n;
		do_shift(&tmp.data[i], a, &next, s8);
	}
	bignum_move(r, &tmp);
	return (1);
}
