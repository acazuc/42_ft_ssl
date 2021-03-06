/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:40:28 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/22 17:25:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

uint64_t	g_bignum_rand = 0;

void	bignum_rand_init(uint64_t init)
{
	g_bignum_rand = init;
}
