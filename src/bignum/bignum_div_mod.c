/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_div_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 21:34:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:50:10 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *tmp)
{
	bignum_clear(tmp);
	return (0);
}

static int	do_part(t_bignum *rm, t_bignum *tmp, int bsign)
{
	rm->sign = 0;
	tmp->sign = 0;
	if (!bignum_is_zero(rm) && !bignum_sub(rm, tmp, rm))
		return (do_clear(tmp));
	rm->sign = bsign;
	return (1);
}

int			bignum_div_mod(t_bignum *dv, t_bignum *rm, t_bignum *a, t_bignum *b)
{
	t_bignum	tmp;
	int			signs;
	int			ret;

	bignum_init(&tmp);
	if (rm && a->sign != b->sign && !bignum_copy(&tmp, b))
		return (do_clear(&tmp));
	signs = (a->sign ? 1 : 0) | (b->sign ? 2 : 0);
	a->sign = 0;
	b->sign = 0;
	ret = bignum_div_mod_op(dv, rm, a, b);
	a->sign = signs & 1;
	b->sign = (signs & 2) >> 1;
	if (dv)
		dv->sign = (signs & 1) != ((signs & 2) >> 1);
	if (rm && signs)
	{
		if (signs == 3)
			rm->sign = 1;
		else if (!do_part(rm, &tmp, signs >> 1))
			return (0);
	}
	bignum_clear(&tmp);
	return (ret);
}
