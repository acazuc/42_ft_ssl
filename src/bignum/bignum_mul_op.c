/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_mul_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:02:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:55:57 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include "libft.h"

static int	do_init(t_bignum *r, t_bignum *a, t_bignum *b, uint32_t *ret)
{
	bignum_trunc(a);
	bignum_trunc(b);
	if (bignum_is_zero(a) || bignum_is_zero(b))
	{
		*ret = 1;
		bignum_zero(r);
		return (1);
	}
	if (bignum_is_one(a))
	{
		*ret = bignum_copy(r, b);
		return (1);
	}
	if (bignum_is_one(b))
	{
		*ret = bignum_copy(r, a);
		return (1);
	}
	return (0);
}

static void	do_loop(t_bignum *tmp, t_bignum *a, t_bignum *b, uint32_t i)
{
	t_bignum_dword	carry;
	t_bignum_dword	ai;
	uint32_t		j;

	carry = 0;
	j = 0;
	ai = a->data[i];
	while (j < b->len)
	{
		carry += tmp->data[i + j] + ai * b->data[j];
		tmp->data[i + j] = carry;
		carry >>= sizeof(*a->data) * 8;
		++j;
	}
	if (carry)
		tmp->data[i + j] += carry;
}

int			bignum_mul_op(t_bignum *r, t_bignum *a, t_bignum *b)
{
	t_bignum	tmp;
	uint32_t	i;

	if (do_init(r, a, b, &i))
		return (i);
	bignum_init(&tmp);
	if (!bignum_resize(&tmp, a->len + b->len))
	{
		bignum_clear(&tmp);
		return (0);
	}
	ft_bzero(tmp.data, (a->len + b->len) * sizeof(*tmp.data));
	i = 0;
	while (i < a->len)
	{
		do_loop(&tmp, a, b, i);
		++i;
	}
	bignum_trunc(&tmp);
	bignum_move(r, &tmp);
	return (1);
}
