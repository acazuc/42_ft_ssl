/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_bignum2bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:45:40 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 13:54:20 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_bignum2bin(t_bignum *a, unsigned char *to)
{
	int	i;
	int	bytes;

	bytes = bignum_num_bytes(a);
	i = 0;
	while (i < bytes)
	{
		to[i] = ((unsigned char*)a->data)[bytes - 1 - i];
		++i;
	}
	return (bytes);
}
