/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_bignum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:46:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 16:57:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

/*int		pem_read_bignum(t_vecu8 *data, t_bignum *bignum)
{
	uint32_t	len;
	int32_t		ret;

	ret = pem_read_len(data->data + data->pos, data->len - data->pos, &len);
	if (ret < 0 || data->pos + len + ret > data->len)
		return (0);
	data->pos += ret;
	if (!bignum_resize(bignum, ret))
		return (0);
	do_read_datas(data, bignum);
	return (1);
}*/

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
		tmp = bignum->data[i / sizeof(*bignum->data)] >> (8 * (i % 4));
		if (!vecu8_push(data, (uint8_t*)&tmp, 1))
			return (0);
		if (!i)
			break;
		--i;
	}
	return (1);
}

int		pem_write_bignum(t_vecu8 *data, t_bignum *bignum)
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
