/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_div_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 21:34:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 23:34:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_part(t_bignum *rm, t_bignum *b, int bsign)
{
	rm->sign = 0;
	b->sign = 0;
	if (!bignum_is_zero(rm) && !bignum_sub(rm, b, rm))
	{
		bignum_free(b);
		return (0);
	}
	rm->sign = bsign;
	bignum_free(b);
	return (1);
}

int	bignum_div_mod(t_bignum *dv, t_bignum *rm, t_bignum *a, t_bignum *b)
{
	t_bignum	*tmp;
	int		asign;
	int		bsign;
	int		ret;

	tmp = NULL;
	if (rm && a->sign != b->sign && !(tmp = bignum_dup(b)))
		return (0);
	asign = a->sign;
	bsign = b->sign;
	a->sign = 0;
	b->sign = 0;
	ret = bignum_div_mod_op(dv, rm, a, b);
	a->sign = asign;
	b->sign = bsign;
	if (dv)
		dv->sign = asign != bsign;
	if (rm && (asign || bsign))
	{
		if (asign && bsign)
			rm->sign = 1;
		else if (!do_part(rm, tmp, bsign))
			return (0);
	}
	return (ret);
}
