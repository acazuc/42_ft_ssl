/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:42:27 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 21:00:34 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_cmp(t_bignum *a, t_bignum *b)
{
	uint64_t	i;

	bignum_trunc(a);
	bignum_trunc(b);
	if (a->len > b->len)
		return (1);
	if (b->len > a->len)
		return (-1);
	if (bignum_is_zero(a))
		return (0);
	i = a->len - 1;
	while (1)
	{
		if (a->data[i] > b->data[i])
			return (1);
		if (b->data[i] > a->data[i])
			return (-1);
		if (!i)
			break;
		--i;
	}
	return (0);
}
