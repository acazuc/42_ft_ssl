/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:27:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 22:48:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

static int	do_clear(t_bignum *result)
{
	bignum_free(result);
	return (0);
}

static int	do_init(t_bignum **result, t_bignum *a, t_bignum *b)
{
	if (bignum_cmp(a, b) < 0)
		return (0);
	if (!(*result = bignum_new()))
		return (0);
	bignum_trunc(a);
	bignum_trunc(b);
	bignum_zero(*result);
	return (1);
}

static int	do_loop(int64_t *carry, t_bignum *result)
{
	if (*carry < 0)
	{
		if (!(bignum_grow(result, *carry + BIGNUM_BASE)))
			return (do_clear(result));
		*carry = -1;
	}
	else
	{
		if (!(bignum_grow(result, *carry)))
			return (do_clear(result));
		*carry = 0;
	}
	return (1);
}

int		bignum_sub(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	*result;
	int64_t		carry;
	uint64_t	i;

	if (!do_init(&result, a, b))
		return (0);
	carry = 0;
	i = 0;
	while (i < a->len)
	{
		carry += a->data[i] - (i < b->len ? b->data[i] : 0);
		if (!do_loop(&carry, result))
			return (0);
		++i;
	}
	bignum_trunc(result);
	if (!(bignum_copy(r, result)))
		return (do_clear(result));
	bignum_free(result);
	return (1);
}
