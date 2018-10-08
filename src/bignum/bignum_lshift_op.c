/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:54:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:52:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *tmp1, t_bignum *tmp2, t_bignum *tmp3)
{
	bignum_clear(tmp1);
	bignum_clear(tmp2);
	bignum_clear(tmp3);
	return (0);
}

static int	do_init(t_bignum *tmp1, t_bignum *tmp2, t_bignum *tmp3)
{
	bignum_init(tmp1);
	bignum_init(tmp2);
	bignum_init(tmp3);
	if (!bignum_grow(tmp1, 2))
		return (0);
	return (1);
}

int			bignum_lshift_op(t_bignum *r, t_bignum *a, uint32_t n)
{
	t_bignum	tmp1;
	t_bignum	tmp2;
	t_bignum	tmp3;

	bignum_trunc(a);
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	if (!do_init(&tmp1, &tmp2, &tmp3))
		return (do_clear(&tmp1, &tmp2, &tmp3));
	if (!bignum_grow(&tmp2, n))
		return (do_clear(&tmp1, &tmp2, &tmp3));
	if (!bignum_exp(&tmp3, &tmp1, &tmp2))
		return (do_clear(&tmp1, &tmp2, &tmp3));
	if (!bignum_mul(r, a, &tmp3))
		return (do_clear(&tmp1, &tmp2, &tmp3));
	do_clear(&tmp1, &tmp2, &tmp3);
	bignum_trunc(r);
	return (1);
}
