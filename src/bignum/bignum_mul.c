/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:36:11 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 18:57:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int		bignum_mul(t_bignum *r, t_bignum *a, t_bignum *b)
{
	int	ret;
	int	tmp;

	if (a->sign == b->sign)
	{
		tmp = a->sign;
		a->sign = 0;
		b->sign = 0;
		ret = bignum_mul_op(r, a, b);
		a->sign = tmp;
		b->sign = tmp;
		r->sign = 0;
		return (ret);
	}
	if (a->sign)
	{
		b->sign = 0;
		ret = bignum_mul_op(r, a, b);
		b->sign = 1;
		r->sign = 1;
		return (ret);
	}
	a->sign = 0;
	ret = bignum_mul_op(r, a, b);
	a->sign = 1;
	r->sign = 1;
	return (ret);
}
