/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_is_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 17:33:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 19:29:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_is_word(t_bignum *bignum, t_bignum_word word)
{
	bignum_trunc(bignum);
	if (!bignum->len)
		return (!word);
	return (!bignum->sign && bignum->data[0] == word);
}
