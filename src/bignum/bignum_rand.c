/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 10:07:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 21:33:46 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <fcntl.h>

static void	do_top_bottom(t_bignum *bignum, uint32_t bits, int top
		, int bottom)
{
	if (bottom == BIGNUM_RAND_BOT_ODD)
		bignum->data[0] |= 1;
	if (top == BIGNUM_RAND_TOP_TWO || top == BIGNUM_RAND_TOP_ONE)
		bignum->data[(bits - 1) / 8 / sizeof(*bignum->data)] |=
			(t_bignum_word)1 << ((bits - 1) % (8 * sizeof(*bignum->data)));
	if (top == BIGNUM_RAND_TOP_TWO && bits > 1)
		bignum->data[(bits - 2) / 8 / sizeof(*bignum->data)] |=
			(t_bignum_word)1 << ((bits - 2) % (8 * sizeof(*bignum->data)));
}

int	bignum_rand(t_bignum *bignum, uint32_t bits, int top, int bottom)
{
	uint32_t	pos;

	if (!bits)
	{
		bignum_zero(bignum);
		return (1);
	}
	if (!bignum_resize(bignum, (bits + (8 * sizeof(*bignum->data) - 1))
				/ 8 / sizeof(*bignum->data)))
		return (0);
	pos = 0;
	while (pos < bits / 8 / sizeof(*bignum->data))
	{
		bignum->data[pos] = bignum_rand_get();
		++pos;
	}
	if (pos < bignum->len)
	{
		bignum->data[pos] = bignum_rand_get() & (((t_bignum_word)1
			<< (bits - pos * 8 * sizeof(*bignum->data))) - 1);
	}
	do_top_bottom(bignum, bits, top, bottom);
	return (1);
}
