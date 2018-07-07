/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_trunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:32:49 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 16:06:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

void	bignum_trunc(t_bignum *bignum)
{
	uint64_t	i;

	if (!bignum->len)
		return ;
	i = bignum->len - 1;
	while (i > 0 && !bignum->data[i])
		--i;
	if (i == bignum->len - 1)
		return ;
	if (!i && !bignum->data[i])
	{
		free(bignum->data);
		bignum->data = NULL;
		bignum->len = 0;
		return ;
	}
	bignum->len = i + 1;
	return ;
}
