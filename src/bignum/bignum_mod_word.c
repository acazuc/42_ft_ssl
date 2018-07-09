/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:25:28 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 13:41:05 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_mod_word(uint32_t *r, t_bignum *a, uint32_t b)
{
	uint64_t	ret;
	uint64_t	i;

	if (!b)
		return (0);
	bignum_trunc(a);
	if (bignum_is_zero(a))
	{
		*r = 0;
		return (1);
	}
	ret = 0;
	i = a->len - 1;
	while (1)
	{
		ret = (ret * (BIGNUM_BASE % b) + a->data[i] % b) % b;
		if (!i)
			break;
		--i;
	}
	*r = ret;
	return (1);
}
