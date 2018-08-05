/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_num_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 21:14:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 21:16:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_num_bytes(t_bignum *bignum)
{
	int	bits;

	bits = bignum_num_bits(bignum);
	return (bits / 8 + (bits % 8 ? 1 : 0));
}
