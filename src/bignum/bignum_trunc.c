/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_trunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:32:49 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 19:46:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

void	bignum_trunc(t_bignum *bignum)
{
	while (bignum->len > 1 && !bignum->data[bignum->len - 1])
		--bignum->len;
}
