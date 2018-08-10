/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:38:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 21:31:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

int	bignum_resize(t_bignum *bignum, uint32_t len)
{
	if (bignum->len == len)
		return (1);
	if (len > bignum->len)
	{
		if (!bignum_reserve(bignum, len))
			return (0);
		ft_memset(bignum->data + bignum->len, 0
				, (len - bignum->len) * sizeof(*bignum->data));
	}
	bignum->len = len;
	return (1);
}
