/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:27:47 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 22:15:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *result)
{
	bignum_free(result);
	return (0);
}

static int	do_init(t_bignum **result, t_bignum *a, t_bignum *b, uint64_t *to)
{
	bignum_trunc(a);
	bignum_trunc(b);
	if (!(*result = bignum_new()))
		return (0);
	bignum_zero(*result);
	*to = a->len > b->len ? a->len : b->len;
	if (!(bignum_reserve(*result, *to)))
		return (do_clear(*result));
	return (1);
}

static int	do_end(t_bignum *result, t_bignum *r, uint64_t carry)
{
	if (carry)
	{
		if (!(bignum_grow(result, carry)))
			return (do_clear(result));
	}
	bignum_trunc(result);
	if (!(bignum_copy(r, result)))
		return (do_clear(result));
	bignum_free(result);
	return (1);
}

int		bignum_add(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	*result;
	uint64_t	carry;
	uint64_t	to;
	uint64_t	i;

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
		if (!(bignum_grow(result, carry % BIGNUM_BASE)))
			return (do_clear(result));
		carry /= BIGNUM_BASE;
		++i;
	}
	return (do_end(result, r, carry));
}
