/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_num_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 20:57:44 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 16:43:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_num_bits(t_bignum *bignum)
{
	int	i;

	bignum_trunc(bignum);
	if (!bignum->len)
		return (0);
	i = 8 * sizeof(*bignum->data) - 1;
	while (i >= 0)
	{
		if ((bignum->data[bignum->len - 1] >> i) & 1)
			break;
		--i;
	}
	return ((bignum->len - 1) * 8 * sizeof(*bignum->data) + (i + 1));
}
