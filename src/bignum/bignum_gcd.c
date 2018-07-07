/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_gcd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 23:10:24 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 10:02:55 by acazuc           ###   ########.fr       */
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
	if (!(*tmp2 = bignum_new()))
		return (0);
	if (!(*tmp3 = bignum_new()))
		return (0);
	return (1);
}

int	bignum_gcd(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	*tmp1;
	t_bignum	*tmp2;
	t_bignum	*tmp3;

	bignum_trunc(a);
	bignum_trunc(b);
	if (!do_init(&tmp1, &tmp2, &tmp3))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!bignum_copy(tmp1, a))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!bignum_copy(tmp2, b))
		return (do_clear(tmp1, tmp2, tmp3));
	while (!bignum_is_zero(tmp2))
	{
		if (!bignum_mod(tmp3, tmp1, tmp2))
			return (do_clear(tmp1, tmp2, tmp3));
		if (!bignum_copy(tmp1, tmp2))
			return (do_clear(tmp1, tmp2, tmp3));
		if (!bignum_copy(tmp2, tmp3))
			return (do_clear(tmp1, tmp2, tmp3));
	}
	bignum_trunc(tmp1);
	if (!bignum_copy(r, tmp1))
		return (do_clear(tmp1, tmp2, tmp3));
	return (1);
}
