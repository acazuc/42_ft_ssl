/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_set_bit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:34:54 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 14:01:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

int	bignum_set_bit(t_bignum *bignum, uint32_t n)
{
	uint32_t	len;
	uint32_t	tmp;

	tmp = n / 8 / sizeof(*bignum->data);
	len = tmp + 1;
	if (bignum->len < len && !bignum_resize(bignum, len))
		return (0);
	bignum->data[tmp] |= (t_bignum_word)1 << (n % (8 * sizeof(*bignum->data)));
	return (1);
}
