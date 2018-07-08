/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:10:22 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 17:49:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_exp(t_bignum *r, t_bignum *a, t_bignum *p)
{
	int	ret;

	if (!a->sign)
	{
		ret = bignum_exp_op(r, a, p);
		r->sign = 0;
		return (ret);
	}
	a->sign = 0;
	ret = bignum_exp_op(r, a, p);
	a->sign = 1;
	r->sign = bignum_is_odd(p);
	return (ret);
}
