/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:42:27 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 22:51:56 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_cmp(t_bignum *a, t_bignum *b)
{
	if (!a->sign && !b->sign)
		return (bignum_ucmp(a, b));
	if (a->sign && b->sign)
		return (-bignum_ucmp(a, b));
	if (bignum_is_zero(a) && bignum_is_zero(b))
		return (0);
	if (a->sign && !b->sign)
		return (-1);
	if (!a->sign && b->sign)
		return (1);
	return (0);
}
