/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:27:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 14:39:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stdlib.h>

void	bignum_free(t_bignum *bignum)
{
	if (!bignum)
		return ;
	bignum_clear(bignum);
	free(bignum);
}
