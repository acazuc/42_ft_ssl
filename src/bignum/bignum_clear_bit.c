/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_clear_bit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 21:03:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:48:59 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_clear_bit(t_bignum *bignum, uint32_t n)
{
	if ((n / 8 + sizeof(*bignum->data) - 1)
			/ sizeof(*bignum->data) > bignum->len)
		return (0);
	bignum->data[n / 8 / sizeof(*bignum->data)] &= ~(1
		<< (n % (8 * sizeof(*bignum->data))));
	return (1);
}
