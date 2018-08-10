/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:55:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:45:03 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

int	bignum_copy(t_bignum *dst, t_bignum *src)
{
	if (dst == src)
		return (1);
	if (!bignum_resize(dst, src->len))
		return (0);
	ft_memcpy(dst->data, src->data, src->len * sizeof(*src->data));
	dst->sign = src->sign;
	return (1);
}
