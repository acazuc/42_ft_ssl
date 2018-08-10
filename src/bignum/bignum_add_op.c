/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_add_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 16:47:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 20:54:33 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *result)
{
	bignum_clear(result);
	return (0);
}

static int	do_init(t_bignum *result, t_bignum *a, t_bignum *b, uint32_t *to)
{
	bignum_trunc(a);
	bignum_trunc(b);
	bignum_init(result);
	bignum_zero(result);
	*to = a->len > b->len ? a->len : b->len;
	if (!bignum_reserve(result, *to))
		return (do_clear(result));
	return (1);
}

static int	do_end(t_bignum *result, t_bignum *r, t_bignum_word carry)
{
	if (carry)
	{
		if (!bignum_grow(result, carry))
			return (do_clear(result));
	}
	bignum_trunc(result);
	if (!bignum_copy(r, result))
		return (do_clear(result));
	bignum_clear(result);
	return (1);
}

int		bignum_add_op(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	result;
	t_bignum_dword	carry;
	uint32_t	to;
	uint32_t	i;

	if (!do_init(&result, a, b, &to))
		return (0);
	carry = 0;
	i = 0;
	while (i < to)
	{
		if (i < a->len)
			carry += a->data[i];
		if (i < b->len)
			carry += b->data[i];
		if (!bignum_grow(&result, carry & (((t_bignum_dword)1
			<< sizeof(*a->data) * 8) - 1)))
			return (do_clear(&result));
		carry >>= sizeof(*a->data) * 8;
		++i;
	}
	return (do_end(&result, r, carry));
}
