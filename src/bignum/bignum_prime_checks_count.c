/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_prime_checks_count.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:51:46 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 17:22:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_prime_checks_count(t_bignum *bignum)
{
	if (bignum->len * 8 * sizeof(*bignum->data) >= 1300)
		return (2);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 850)
		return (3);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 650)
		return (4);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 550)
		return (5);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 450)
		return (6);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 400)
		return (7);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 350)
		return (8);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 300)
		return (9);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 250)
		return (12);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 200)
		return (15);
	if (bignum->len * 8 * sizeof(*bignum->data) >= 150)
		return (18);
	return (27);
}
