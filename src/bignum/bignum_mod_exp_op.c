/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod_exp_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:10:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/19 16:54:33 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stddef.h>

static int	do_clear(t_bignum *base, t_bignum *res, t_bignum *ex)
{
	bignum_clear(base);
	bignum_clear(res);
	bignum_clear(ex);
	return (0);
}

static int	do_loop(t_bignum *res, t_bignum *base, t_bignum *ex, t_bignum *m)
{
	if (bignum_is_odd(ex))
	{
		if (!bignum_mul_op(res, res, base))
			return (0);
		if (!bignum_div_mod_op(NULL, res, res, m))
			return (0);
	}
	if (!bignum_sqr_op(base, base))
		return (0);
	if (!bignum_div_mod_op(NULL, base, base, m))
		return (0);
	if (!bignum_rshift1_op(ex, ex))
		return (0);
	return (1);
}

static int	do_init(t_bignum *a, t_bignum *r, t_bignum *p, int *ret)
{
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		*ret = 1;
		return (1);
	}
	if (bignum_is_zero(p))
	{
		*ret = bignum_one(r);
		return (1);
	}
	return (0);
}

int			bignum_mod_exp_op(t_bignum *r, t_bignum *a, t_bignum *p
		, t_bignum *m)
{
	t_bignum	base;
	t_bignum	ex;
	t_bignum	res;
	int			ret;

	if (do_init(a, r, p, &ret))
		return (ret);
	if (bignum_is_one(p))
		return (bignum_copy(r, a));
	bignum_init(&base);
	bignum_init(&ex);
	bignum_init(&res);
	if (!bignum_copy(&ex, p) || !bignum_copy(&base, a)
	|| !bignum_div_mod_op(NULL, &base, &base, m) || !bignum_grow(&res, 1))
		return (do_clear(&base, &res, &ex));
	while (!bignum_is_zero(&ex))
		if (!do_loop(&res, &base, &ex, m))
			return (do_clear(&base, &res, &ex));
	bignum_trunc(&res);
	bignum_move(r, &res);
	do_clear(&base, &res, &ex);
	return (1);
}
