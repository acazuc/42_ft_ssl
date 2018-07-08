/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 14:32:28 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 19:05:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_mod_exp(t_bignum *r, t_bignum *a, t_bignum *p, t_bignum *m)
{
	int	ret;

	if (!a->sign)
	{
		ret = bignum_mod_exp_op(r, a, p, m);
		r->sign = 0;
		return (ret);
	}
	a->sign = 0;
	ret = bignum_mod_exp_op(r, a, p, m);
	a->sign = 1;
	r->sign = bignum_is_odd(p);
	return (ret);
}
