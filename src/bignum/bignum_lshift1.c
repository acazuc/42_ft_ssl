/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:48:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 12:57:01 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_lshift1(t_bignum *r, t_bignum *a)
{
	t_bignum	*tmp;

	if (!(tmp = bignum_new()))
		return (0);
	if (!(bignum_grow(tmp, 2)))
	{
		bignum_free(tmp);
		return (0);
	}
	if (!(bignum_mul(r, a, tmp)))
	{
		bignum_free(tmp);
		return (0);
	}
	bignum_free(tmp);
	return (1);
}
