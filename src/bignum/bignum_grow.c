/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_grow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:00:53 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 19:29:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_grow(t_bignum *bignum, t_bignum_word a)
{
	if (!bignum_resize(bignum, bignum->len + 1))
		return (0);
	bignum->data[bignum->len - 1] = a;
	return (1);
}
