/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:10:22 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 17:18:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *tmp[2])
{
	bignum_free(tmp[0]);
	bignum_free(tmp[1]);
	return (0);
}

static int	do_part1(t_bignum **tmp1, t_bignum **tmp2, t_bignum *a, t_bignum *p)
{
	*tmp1 = NULL;
	*tmp2 = NULL;
	if (!(*tmp1 = bignum_new()))
		return (0);
	if (!(*tmp2 = bignum_new()))
		return (0);
	if (!(bignum_rshift1(*tmp1, p)))
		return (0);
	if (!(bignum_exp(*tmp2, a, *tmp1)))
		return (0);
	if (!(bignum_mul(*tmp1, *tmp2, *tmp2)))
		return (0);
	return (1);
}

static int	do_part2(t_bignum *tmp[2], t_bignum *r)
{
	if (!(bignum_copy(r, tmp[0])))
		return (do_clear(tmp));
	bignum_free(tmp[0]);
	bignum_free(tmp[1]);
	bignum_trunc(r);
	return (1);
}

static int	do_part3(t_bignum *tmp[2], t_bignum *a, t_bignum *r)
{
	if (!(bignum_mul(tmp[1], tmp[0], a)))
		return (do_clear(tmp));
	if (!(bignum_copy(r, tmp[1])))
		return (do_clear(tmp));
	bignum_free(tmp[0]);
	bignum_free(tmp[1]);
	bignum_trunc(r);
	return (1);
}

int	bignum_exp(t_bignum *r, t_bignum *a, t_bignum *p)
{
	t_bignum	*tmp[2];

	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	if (bignum_is_zero(p))
		return (bignum_one(r));
	if (bignum_is_one(p))
		return (bignum_copy(r, a));
	if (!do_part1(&tmp[0], &tmp[1], a, p))
		return (do_clear(tmp));
	if (!bignum_is_odd(p))
		return (do_part2(tmp, r));
	return (do_part3(tmp, a, r));
}
