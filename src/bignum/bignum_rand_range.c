/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 13:46:21 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 20:06:37 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_rand_range(t_bignum *bignum, t_bignum *range, int top
		, int bottom)
{
	bignum_trunc(range);
	if (!bignum_rand(bignum, range->len * 8 * sizeof(*bignum->data), top
					, bottom))
		return (0);
	if (!bignum_mod(bignum, bignum, range))
		return (0);
	bignum_trunc(bignum);
	return (1);
}
