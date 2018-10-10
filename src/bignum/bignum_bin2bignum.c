/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_bin2bginum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:38:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 13:53:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stddef.h>

t_bignum	*bignmu_bin2bignum(unsigned char *s, int len, t_bignum *ret)
{
	int	i;

	if (!ret)
		ret = bignum_new();
	if (!ret)
		return (NULL);
	if (!bignum_resize(ret, len / sizeof(*ret->data)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char*)ret->data)[len - 1 - i] = s[i];
		++i;
	}
	return (ret);
}
