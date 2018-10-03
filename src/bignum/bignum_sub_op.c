/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_op_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 16:50:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/17 20:06:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_init(t_bignum *result, t_bignum *a, t_bignum *b)
{
	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_ucmp(a, b) < 0)
		return (0);
	bignum_init(result);
	if (!bignum_resize(result, a->len))
		return (0);
	return (1);
}

int		bignum_sub_op(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	result;
	t_bignum_sdword	carry;
	uint32_t	i;

	if (!do_init(&result, a, b))
		return (0);
	carry = 0;
	i = 0;
	while (i < a->len)
	{
		carry += a->data[i];
		if (i < b->len)
			carry -= b->data[i];
		result.data[i] = carry;
		carry = carry < 0 ? -1 : 0;
		++i;
	}
	bignum_trunc(&result);
	bignum_move(r, &result);
	return (1);
}
