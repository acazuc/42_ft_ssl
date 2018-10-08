/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:25:28 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:53:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_mod_word(t_bignum_word *r, t_bignum *a, t_bignum_word b)
{
	t_bignum_dword	ret;
	t_bignum_dword	tmp;
	uint32_t		i;

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
	tmp = ((t_bignum_dword)1 << (sizeof(a->data) * 8)) % b;
	while (1)
	{
		ret = (ret * tmp + a->data[i] % b) % b;
		if (!i)
			break ;
		--i;
	}
	*r = ret;
	return (1);
}
