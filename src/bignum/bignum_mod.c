/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:52:50 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 21:44:05 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

/*static int	do_clear(t_bignum *tmp1, t_bignum *tmp2, t_bignum *tmp3)
{
	bignum_free(tmp1);
	bignum_free(tmp2);
	bignum_free(tmp3);
	return (0);
}*/

int	bignum_mod(t_bignum *r, t_bignum *a, t_bignum *b)
{
	return (bignum_div_mod(NULL, r, a, b));
	/*t_bignum	*tmp1;
	t_bignum	*tmp2;
	t_bignum	*tmp3;
	uint64_t	tmp;
	uint64_t	i;
	uint64_t	x;
	uint64_t	l;
	uint64_t	s;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_is_zero(b))
		return (do_clear(tmp1, tmp2, tmp3));
	if (bignum_is_zero(a))
	{
		bignum_zero(r);
		return (1);
	}
	if (!(tmp1 = bignum_new()))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!(tmp2 = bignum_new()))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!bignum_resize(tmp2, 1))
		return (do_clear(tmp1, tmp2, tmp3));
	if (!(tmp3 = bignum_new()))
		return (do_clear(tmp1, tmp2, tmp3));
	bignum_zero(r);
	i = a->len - 1;
	while (1)
	{
		if (!bignum_grow_front(tmp1, a->data[i]))
			return (do_clear(tmp1, tmp2, tmp3));
		x = 0;
		l = 0;
		s = BIGNUM_BASE;
		while (l <= s)
		{
			tmp = (l + s) >> 1;
			tmp2->data[0] = tmp;
			if (!bignum_mul(tmp3, b, tmp2))
				return (do_clear(tmp1, tmp2, tmp3));
			if (bignum_cmp(tmp3, r) > 0)
			{
				x = tmp;
				s = tmp - 1;
			}
			else
				s = tmp + 1;
		}
		tmp2->data[0] = x - 1;
		if (!bignum_mul(tmp3, tmp2, b))
			return (do_clear(tmp1, tmp2, tmp3));
		if (!bignum_sub(tmp4, tmp1, tmp3))
			return (do_clear(tmp1, tmp2, tmp3));
		if (!(bignum_copy(tmp1, tmp4)))
			return (do_clear(tmp1, tmp2, tmp3));
		if (!i)
			break;
		--i;
	}
	bignum_trunc(r);
	return (1);*/
}
