/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:10:22 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 23:01:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *tmp1, t_bignum *tmp2)
{
	bignum_free(tmp1);
	bignum_free(tmp2);
	return (0);
}

int	bignum_exp(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	*tmp1;
	t_bignum	*tmp2;

	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	tmp1 = NULL;
	tmp2 = NULL;
	if (bignum_is_zero(b))
		return (bignum_one(r));
	if (bignum_is_one(b))
		return (bignum_copy(r, a));
	if ((!(tmp1 = bignum_new())))
		return (do_clear(tmp1, tmp2));
	if (!(tmp2 = bignum_new()))
		return (do_clear(tmp1, tmp2));
	if (!(bignum_rshift1(tmp1, b)))
		return (do_clear(tmp1, tmp2));
	if (!(bignum_exp(tmp2, a, tmp1)))
		return (do_clear(tmp1, tmp2));
	if (!(bignum_mul(tmp1, tmp2, tmp2)))
		return (do_clear(tmp1, tmp2));
	if (!bignum_is_odd(b))
	{
		if (!(bignum_copy(r, tmp1)))
			return (do_clear(tmp1, tmp2));
		return (1);
	}
	if (!(bignum_mul(tmp2, tmp1, a)))
		return (do_clear(tmp1, tmp2));
	if (!(bignum_copy(r, tmp2)))
		return (do_clear(tmp1, tmp2));
	bignum_free(tmp1);
	bignum_free(tmp2);
	return (1);
}
