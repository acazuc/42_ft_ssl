/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_set_bit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:34:54 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 20:52:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_set_bit(t_bignum *bignum, uint64_t n)
{
	uint64_t	len;
	uint64_t	old;

	old = bignum->len;
	len = 1 + n / 8 / sizeof(*bignum->data);
	if (bignum->len < len && !bignum_resize(bignum, len))
		return (0);
	if (old < len)
		ft_memset(bignum->data + old, 0, (len - old) * sizeof(*bignum->data));
	bignum->data[n / 8 / sizeof(*bignum->data)] |= 1
		<< (n % (8 * sizeof(*bignum->data)));
	return (1);
}
