/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_bin2bginum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:38:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 12:00:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stddef.h>

t_bignum	*bignum_bin2bignum(unsigned char *s, int len, t_bignum *ret)
{
	int	i;

	if (!ret)
	{
		if (!(ret = bignum_new()))
			return (NULL);
	}
	if (!bignum_resize(ret, (len + sizeof(*ret->data) - 1)
				/ sizeof(*ret->data)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char*)ret->data)[len - 1 - i] = s[i];
		++i;
	}
	return (ret);
}
