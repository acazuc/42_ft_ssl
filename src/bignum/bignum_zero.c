/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:09:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 12:50:21 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

void	bignum_zero(t_bignum *bignum)
{
	free(bignum->data);
	bignum->data = NULL;
	bignum->cap = 0;
	bignum->len = 0;
}
