/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:11:52 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 21:04:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_rshift(t_bignum *r, t_bignum *a, uint32_t n)
{
	int	sign;
	int	ret;

	sign = a->sign;
	ret = bignum_rshift_op(r, a, n);
	r->sign = sign;
	return (ret);
}
