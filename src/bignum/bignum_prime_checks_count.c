/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_prime_checks_count.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:51:46 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 13:00:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_prime_checks_count(t_bignum *bignum)
{
	if (bignum->len * 8 >= 1300)
		return (2);
	if (bignum->len * 8 >= 850)
		return (3);
	if (bignum->len * 8 >= 650)
		return (4);
	if (bignum->len * 8 >= 550)
		return (5);
	if (bignum->len * 8 >= 450)
		return (6);
	if (bignum->len * 8 >= 400)
		return (7);
	if (bignum->len * 8 >= 350)
		return (8);
	if (bignum->len * 8 >= 300)
		return (9);
	if (bignum->len * 8 >= 250)
		return (12);
	if (bignum->len * 8 >= 200)
		return (15);
	if (bignum->len * 8 >= 150)
		return (18);
	return (27);
}
