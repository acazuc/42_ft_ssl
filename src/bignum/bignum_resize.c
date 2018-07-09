/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:38:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 21:17:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_resize(t_bignum *bignum, uint64_t len)
{
	if (bignum->len == len)
		return (1);
	if (!bignum_reserve(bignum, len))
		return (0);
	bignum->len = len;
	return (1);
}
