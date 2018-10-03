/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift1_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:53:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/17 20:03:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_init(t_bignum *r, t_bignum *a, uint32_t *ret)
{
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		*ret = 1;
		return (1);
	}
	if (!bignum_resize(r, a->len + 1))
	{
		*ret = 0;
		return (1);
	}
	return (0);
}

int		bignum_lshift1_op(t_bignum *r, t_bignum *a)
{
	t_bignum_word	carry;
	t_bignum_word	tmp;
	t_bignum_word	msk;
	uint32_t	i;

	if (do_init(r, a, &i))
		return (i);
	carry = 0;
	i = 0;
	msk = (t_bignum_word)1 << (sizeof(*a->data) * 8 - 1);
	while (i < a->len)
	{
		tmp = a->data[i] & msk;
		tmp >>= sizeof(*a->data) * 8 - 1;
		r->data[i] = (a->data[i] << 1) | carry;
		carry = tmp;
		++i;
	}
	if (carry)
		r->data[i] = carry;
	bignum_trunc(r);
	return (1);
}
