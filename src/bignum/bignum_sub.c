/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:27:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:55:27 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_part(t_bignum *r, t_bignum *a, t_bignum *b)
{
	int	ret;

	if (a->sign && b->sign)
	{
		b->sign = 0;
		ret = bignum_add(r, a, b);
		b->sign = 1;
		return (ret);
	}
	if (a->sign && !b->sign)
	{
		a->sign = 0;
		ret = bignum_add_op(r, a, b);
		a->sign = 1;
		r->sign = 1;
		return (ret);
	}
	return (0);
}

int			bignum_sub(t_bignum *r, t_bignum *a, t_bignum *b)
{
	int	ret;

	if (!a->sign && !b->sign && bignum_cmp(a, b) >= 0)
	{
		ret = bignum_sub_op(r, a, b);
		r->sign = 0;
		return (ret);
	}
	if (!a->sign && !b->sign)
	{
		ret = bignum_sub_op(r, b, a);
		r->sign = 1;
		return (ret);
	}
	if ((a->sign && b->sign) || (a->sign && !b->sign))
		return (do_part(r, a, b));
	b->sign = 0;
	ret = bignum_add_op(r, a, b);
	if (r != b)
		b->sign = 1;
	return (ret);
}
