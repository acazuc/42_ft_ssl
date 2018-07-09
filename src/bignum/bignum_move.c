/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 19:26:25 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 22:45:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

void	bignum_move(t_bignum *a, t_bignum *b)
{
	if (a == b)
		return;
	free(a->data);
	a->data = b->data;
	a->len = b->len;
	a->cap = b->cap;
	a->sign = b->sign;
	b->data = NULL;
	b->len = 0;
	b->cap = 0;
	b->sign = 0;
}
