/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:27:47 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 18:55:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int		bignum_add(t_bignum *r, t_bignum *a, t_bignum *b)
{
	int	ret;

	if (!a->sign && !b->sign)
	{
		ret = bignum_add_op(r, a, b);
		r->sign = 0;
	}
	else if (a->sign && b->sign)
	{
		ret = bignum_add_op(r, a, b);
		r->sign = 1;
	}
	else if (!a->sign && b->sign)
	{
		b->sign = 0;
		ret = bignum_sub(r, a, b);
		if (b != r)
			b->sign = 1;
	}
	else
	{
		a->sign = 0;
		ret = bignum_sub(r, b, a);
		if (a != r)
			a->sign = 1;
	}
	return (ret);
}
