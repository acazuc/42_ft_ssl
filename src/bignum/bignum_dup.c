/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:56:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 16:57:52 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

t_bignum	*bignum_dup(t_bignum *bignum)
{
	t_bignum	*tmp;

	if (!(tmp = bignum_new()))
		return (NULL);
	if (!(bignum_copy(tmp, bignum)))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
