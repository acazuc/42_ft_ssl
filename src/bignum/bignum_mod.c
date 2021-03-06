/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:52:50 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:57:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stddef.h>

int	bignum_mod(t_bignum *r, t_bignum *a, t_bignum *b)
{
	return (bignum_div_mod(NULL, r, a, b));
}
