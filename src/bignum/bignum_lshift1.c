/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_lshift1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:48:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 17:53:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_lshift1(t_bignum *r, t_bignum *a)
{
	int	sign;
	int	ret;

	sign = a->sign;
	ret = bignum_lshift1_op(r, a);
	r->sign = sign;
	return (ret);
}
