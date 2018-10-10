/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_bignum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:46:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 13:44:03 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

static int	do_read_datas(t_vecu8 *data, uint32_t len, t_bignum *bignum)
{
	uint32_t	i;

	if (data->data[0] & 0x80)
		bignum->sign = 1;
	bignum->data[0] = data->data[0] & (~0x80);
	i = 1;
	while (i < len)
	{
		bignum->data[i / sizeof(*bignum->data)] |=
			((t_bignum_word)data->data[i])
			<< (8 * (i % sizeof(*bignum->data)));
		++i;
	}
	return (1);
}

int			pem_read_bignum(t_vecu8 *data, t_bignum *bignum)
{
	uint32_t	len;
	int32_t		ret;

	ret = pem_read_len(data->data, data->size, &len);
	if (ret < 0 || len + ret > data->size)
		return (0);
	data->data += ret;
	data->size -= ret;
	bignum_zero(bignum);
	if (!len)
		return (1);
	if (!bignum_resize(bignum, (len + sizeof(*bignum->data) - 1)
				/ sizeof(*bignum->data)))
		return (0);
	do_read_datas(data, len, bignum);
	return (1);
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

int			pem_write_bignum(t_vecu8 *data, t_bignum *bignum)
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
