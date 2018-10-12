/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_rsa_priv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:45:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 14:18:42 by acazuc           ###   ########.fr       */
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
	if ((ret = pem_bignum_read(ctx->d, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if ((ret = pem_bignum_read(ctx->p, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if ((ret = pem_bignum_read(ctx->q, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if ((ret = pem_bignum_read(ctx->dmp, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if ((ret = pem_bignum_read(ctx->dmq, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	if ((ret = pem_bignum_read(ctx->coef, data + readed, len - readed)) == -1)
		return (0);
	readed += ret;
	return (readed == len);
}

int	pem_read_rsa_priv(t_rsa_ctx *ctx, void *data, size_t len)
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
	if (len < readed + 3)
		return (0);
	if (ft_memcpy(data + readed, (uint8_t*)"\x2\x1\x0", 3))
		return (0);
	readed += 3;
	if (!read_bignums(ctx, data, len, readed))
		return (0);
	return (1);
}
