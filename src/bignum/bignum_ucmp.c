/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_ucmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:53:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 19:47:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_ucmp(t_bignum *a, t_bignum *b)
{
	uint64_t	i;

	if (a->len > b->len)
		return (1);
	if (b->len > a->len)
		return (-1);
	if (!a->len)
		return (0);
	i = a->len - 1;
	while (1)
	{
		if (a->data[i] > b->data[i])
			return (1);
		if (b->data[i] > a->data[i])
			return (-1);
		if (!i)
			break;
		--i;
	}
	return (0);
}
