/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:30:34 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 16:52:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_one(t_bignum *bignum)
{
	if (!(bignum_resize(bignum, 1)))
		return (0);
	bignum->data[0] = 1;
	bignum->sign = 0;
	return (1);
}
