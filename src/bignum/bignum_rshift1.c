/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rshift1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:38:26 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 17:39:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_rshift1(t_bignum *r, t_bignum *a)
{
	t_bignum	*tmp;

	if (!(tmp = bignum_new()))
		return (0);
	if (!(bignum_grow(tmp, 2)))
	{
		bignum_free(tmp);
		return (0);
	}
	if (!(bignum_div(r, a, tmp)))
	{
		bignum_free(tmp);
		return (0);
	}
	bignum_free(tmp);
	return (1);
}
