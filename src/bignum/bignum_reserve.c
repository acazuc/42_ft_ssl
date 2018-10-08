/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:11:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:54:59 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

int	bignum_reserve(t_bignum *bignum, uint32_t len)
{
	t_bignum_word	*tmp;
	uint32_t		npot;

	if (len <= bignum->cap)
		return (1);
	npot = bignum_npot(len);
	if (npot < 32)
		npot = 32;
	if (!(tmp = malloc(sizeof(*tmp) * npot)))
		return (0);
	ft_memcpy(tmp, bignum->data, bignum->len * sizeof(*tmp));
	free(bignum->data);
	bignum->data = tmp;
	bignum->cap = npot;
	return (1);
}
