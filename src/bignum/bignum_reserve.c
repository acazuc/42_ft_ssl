/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:11:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 21:18:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_reserve(t_bignum *bignum, uint64_t len)
{
	uint32_t	*tmp;
	uint64_t	npot;

	if (len <= bignum->cap)
		return (1);
	npot = bignum_npot(len);
	if (npot < 8)
		npot = 8;
	if (!(tmp = malloc(sizeof(*tmp) * npot)))
		return (0);
	ft_memcpy(tmp, bignum->data, bignum->len * sizeof(*tmp));
	free(bignum->data);
	bignum->data = tmp;
	bignum->cap = npot;
	return (1);
}
