/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:38:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/17 15:17:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

int	bignum_resize(t_bignum *bignum, uint32_t len)
{
	if (len <= bignum->len)
	{
		bignum->len = len;
		return (1);
	}
	if (!bignum_reserve(bignum, len))
		return (0);
	ft_bzero(bignum->data + bignum->len
			, (len - bignum->len) * sizeof(*bignum->data));
	bignum->len = len;
	return (1);
}
