/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 22:20:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:44:06 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stddef.h>

void	bignum_init(t_bignum *bignum)
{
	bignum->data = NULL;
	bignum->len = 0;
	bignum->sign = 0;
	bignum->cap = 0;
}
