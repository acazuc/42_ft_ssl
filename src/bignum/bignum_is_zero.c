/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_is_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:46:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 17:34:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_is_zero(t_bignum *bignum)
{
	bignum_trunc(bignum);
	if (!bignum->len)
		return (1);
	return (0);
}
