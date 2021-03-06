/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:26:43 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 21:04:12 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_lshift(t_bignum *r, t_bignum *a, uint32_t n)
{
	int	sign;
	int	ret;

	sign = a->sign;
	ret = bignum_lshift_op(r, a, n);
	r->sign = sign;
	return (ret);
}
