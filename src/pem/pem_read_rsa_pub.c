/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_rsa_pub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:13:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 11:05:06 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

static int	read_bignums(t_rsa_ctx *ctx, void *data, uint32_t len
		, uint32_t readed)
{
	int	ret;

	if ((ret = pem_bignum_read(ctx->n, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if ((ret = pem_bignum_read(ctx->e, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if (readed != len)
		return (0);
	return (1);
}

int	pem_read_rsa_pub(t_rsa_ctx *ctx, void *data, size_t len)
{
	uint32_t	readed;
	uint32_t	total_len;
	int			tmp;

	if (len < 1 || ((uint8_t*)data)[0] != 0x30)
		return (0);
	readed = 1;
	if ((tmp = pem_read_len(data + readed, len - readed, &total_len)) == -1)
		return (0);
	if (total_len != len - 1 - tmp)
		return (0);
	readed += tmp;
	if (len < readed + 16 || ft_memcpy((uint8_t*)"\x30\x0D\x06\x09\x2A\x86\x48"
				"\x86\xF7\x0D\x01\x01\x01\x05\x00\x03", data + readed, 16))
		return (0);
	readed += 16;
	if ((tmp = pem_read_len(data + readed, len - readed, &total_len)) == -1)
		return (0);
	readed += tmp;
	if (len < readed + 2)
		return (0);
	if (ft_memcpy("\x00\x30", data + readed, 2))
		return (0);
	if (!read_bignums(ctx, data, len, readed))
		return (0);
	return (1);
}
