/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_bignum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:46:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 17:35:57 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

static int	do_write_datas(t_vecu8 *data, t_bignum *bignum)
{
	uint64_t	i;
	uint32_t	tmp;

	i = bignum->len - 1;
	while (1)
	{
		tmp = ft_swap_uint(bignum->data[i]);
		if (!vecu8_push(data, (uint8_t*)&tmp, 4))
			return (0);
		if (!i)
			break;
		--i;
	}
	return (1);
}

int	pem_write_bignum(t_vecu8 *data, t_bignum *bignum)
{
	uint8_t	tmp[5];

	if (!vecu8_pushu8(data, 0x02))
		return (0);
	if (!bignum->len)
	{
		if (!vecu8_pushu8(data, 2))
			return (0);
		if (!vecu8_pushu8(data, 0))
			return (0);
		if (!vecu8_pushu8(data, 0))
			return (0);
		return (1);
	}
	if (!vecu8_push(data, tmp, pem_write_len(tmp, 1 + bignum->len
					* sizeof(*bignum->data))))
		return (0);
	if (!vecu8_pushu8(data, bignum->sign ? 1 : 0))
		return (0);
	if (!do_write_datas(data, bignum))
		return (0);
	return (1);
}
