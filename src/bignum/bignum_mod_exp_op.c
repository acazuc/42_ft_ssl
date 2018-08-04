/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod_exp_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:10:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 14:58:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *base, t_bignum *res, t_bignum *ex)
{
	bignum_free(base);
	bignum_clear(res);
	bignum_free(ex);
	return (0);
}

static int	do_loop(t_bignum *res, t_bignum *base, t_bignum *ex, t_bignum *m)
{
	if (bignum_is_odd(ex))
	{
		if (!bignum_mul(res, res, base))
			return (0);
		if (!bignum_mod(res, res, m))
			return (0);
	}
	if (!bignum_mul(base, base, base))
		return (0);
	if (!bignum_mod(base, base, m))
		return (0);
	if (!bignum_rshift1(ex, ex))
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

int	bignum_mod_exp_op(t_bignum *r, t_bignum *a, t_bignum *p, t_bignum *m)
{
	t_bignum	*base;
	t_bignum	*ex;
	t_bignum	res;
	int		ret;

	if (do_init(a, r, p, &ret))
		return (ret);
	if (bignum_is_one(p))
		return (bignum_copy(r, a));
	base = NULL;
	ex = NULL;
	bignum_init(&res);
	if (!(ex = bignum_dup(p))
			|| !(base = bignum_dup(a))
			|| !(bignum_mod(base, base, m)) || !bignum_grow(&res, 1))
		return (do_clear(base, &res, ex));
	while (!bignum_is_zero(ex))
		if (!do_loop(&res, base, ex, m))
			return (do_clear(base, &res, ex));
	bignum_trunc(&res);
	bignum_move(r, &res);
	do_clear(base, &res, ex);
	return (1);
}
