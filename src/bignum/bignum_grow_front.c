/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_grow_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:32:46 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 19:12:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_grow_front(t_bignum *bignum, uint32_t a)
{
	if (!bignum_resize(bignum, bignum->len + 1))
		return (0);
	ft_memmove(bignum->data + 1, bignum->data, sizeof(*bignum->data)
			* (bignum->len - 1));
	bignum->data[0] = a;
	return (1);
}
