/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:11:52 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 22:58:26 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *tmp1, t_bignum *tmp2, t_bignum *tmp3)
{
	bignum_free(tmp1);
	bignum_free(tmp2);
	bignum_free(tmp3);
	return (0);
}

static int	do_init(t_bignum **tmp1, t_bignum **tmp2, t_bignum **tmp3)
{
	*tmp1 = NULL;
	*tmp2 = NULL;
	*tmp3 = NULL;
	if (!(*tmp1 = bignum_new()))
		return (0);
	if (!bignum_grow(*tmp1, 2))
		return (0);
	if (!(*tmp2 = bignum_new()))
		return (0);
	if (!(*tmp3 = bignum_new()))
		return (0);
	return (1);
}

int		bignum_rshift(t_bignum *r, t_bignum *a, uint64_t n)
{
	t_bignum	*tmp1;
	t_bignum	*tmp2;
	t_bignum	*tmp3;

	bignum_trunc(a);
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	if (!do_init(&tmp1, &tmp2, &tmp3))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!bignum_grow(tmp2, n))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!bignum_exp(tmp3, tmp1, tmp2))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!bignum_div(r, a, tmp3))
		return (do_clear(tmp1, tmp2, tmp3));
	bignum_free(tmp1);
	bignum_free(tmp2);
	bignum_free(tmp3);
	bignum_trunc(r);
	return (1);
}
