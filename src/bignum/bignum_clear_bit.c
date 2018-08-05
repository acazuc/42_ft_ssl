/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_clear_bit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 21:03:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 21:03:33 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_clear_bit(t_bignum *bignum, uint32_t n)
{
	uint32_t	len;
	uint32_t	old;

	old = bignum->len;
	len = 1 + n / 8 / sizeof(*bignum->data);
	if (bignum->len < len && !bignum_resize(bignum, len))
		return (0);
	if (old < len)
		ft_memset(bignum->data + old, 0, (len - old) * sizeof(*bignum->data));
	bignum->data[n / 8 / sizeof(*bignum->data)] &= ~(1
		<< (n % (8 * sizeof(*bignum->data))));
	return (1);
}
