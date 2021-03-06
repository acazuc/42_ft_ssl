/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_is_bit_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:29:28 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/17 20:08:17 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_is_bit_set(t_bignum *bignum, uint32_t n)
{
	uint32_t	tmp;

	tmp = n / 8 / sizeof(*bignum->data);
	if (bignum->len <= tmp)
		return (0);
	return ((bignum->data[tmp] >> (n % (8 * sizeof(*bignum->data)))) & 1);
}
