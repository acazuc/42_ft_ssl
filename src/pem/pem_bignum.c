/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_bignum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:46:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 11:10:10 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

static void	do_read_datas(void *data, uint32_t bn_len, t_bignum *bignum)
{
	uint32_t	i;

	if (((uint8_t*)data)[0] & 0x80)
		bignum->sign = 1;
	else
		bignum->sign = 0;
	bignum->data[0] = ((uint8_t*)data)[0] & (~0x80);
	i = 1;
	while (i < bn_len)
	{
		bignum->data[i / sizeof(*bignum->data)] |=
			(((t_bignum_word*)data)[i])
			<< (8 * (i % sizeof(*bignum->data)));
		++i;
	}
}

int			pem_bignum_read(t_bignum *bignum, void *data, size_t len)
{
	uint32_t	bn_len;
	int32_t		ret;

	ret = pem_read_len(data, len, &bn_len);
	if (ret < 0 || bn_len + ret > len)
		return (-1);
	bignum_zero(bignum);
	if (!bn_len)
		return (ret);
	if (!bignum_resize(bignum, (bn_len + sizeof(*bignum->data) - 1)
				/ sizeof(*bignum->data)))
		return (-1);
	do_read_datas(data, bn_len, bignum);
	return (ret + bn_len);
}

uint32_t	pem_bignum_len(t_bignum *bignum)
{
	if (bignum_num_bits(bignum) % 8)
		return (bignum_num_bytes(bignum));
	if (bignum_is_bit_set(bignum, bignum_num_bits(bignum) - 1))
		return (bignum_num_bytes(bignum) + 1);
	return (bignum_num_bytes(bignum));
}

static int	do_write_datas(t_vecu8 *data, t_bignum *bignum)
{
	uint64_t	i;
	uint8_t		tmp;

	if (!(bignum_num_bits(bignum) % 8)
			&& bignum_is_bit_set(bignum, bignum_num_bits(bignum) - 1))
	{
		if (!vecu8_pushu8(data, bignum->sign ? 0x80 : 0))
			return (0);
	}
	i = bignum_num_bytes(bignum) - 1;
	while (1)
	{
		tmp = bignum->data[i / sizeof(*bignum->data)]
			>> (8 * (i % sizeof(*bignum->data)));
		if (!vecu8_push(data, (uint8_t*)&tmp, 1))
			return (0);
		if (!i)
			break ;
		--i;
	}
	return (1);
}

int			pem_bignum_write(t_vecu8 *data, t_bignum *bignum)
{
	uint8_t		tmp[5];

	if (!vecu8_pushu8(data, 0x02))
		return (0);
	if (!bignum_num_bits(bignum))
	{
		if (!vecu8_pushu8(data, 1))
			return (0);
		if (!vecu8_pushu8(data, 0))
			return (0);
		return (1);
	}
	if (!vecu8_push(data, tmp
				, pem_write_len(tmp, pem_bignum_len(bignum))))
		return (0);
	if (!do_write_datas(data, bignum))
		return (0);
	return (1);
}
