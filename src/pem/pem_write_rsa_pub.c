/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_rsa_pub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:14:20 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 12:25:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

static int	do_clear(t_vecu8 *vec)
{
	vecu8_free(vec);
	return (-1);
}

static int	write_bignums(t_vecu8 *vec, t_rsa_ctx *ctx)
{
	if (!pem_write_bignum(vec, ctx->n))
		return (0);
	if (!pem_write_bignum(vec, ctx->e))
		return (0);
	return (1);
}

static int	get_len(t_rsa_ctx *ctx)
{
	int	total;

	total = 0;
	total += pem_len_len(pem_bignum_len(ctx->n));
	total += pem_bignum_len(ctx->n) + 1;
	total += pem_len_len(pem_bignum_len(ctx->e));
	total += pem_bignum_len(ctx->e) + 1;
	return (total);
}

int			pem_write_rsa_pub(char **dst, t_rsa_ctx *ctx)
{
	t_vecu8	vec;
	int		len;
	int		len_len;
	uint8_t	tmp[64];

	vecu8_init(&vec);
	if (!vecu8_pushu8(&vec, 0x30))
		return (do_clear(&vec));
	len = get_len(ctx);
	len_len = pem_len_len(len);
	if (!vecu8_push(&vec, tmp, pem_write_len(tmp, 15 + len + 4 + len_len)))
		return (do_clear(&vec));
	if (!vecu8_push(&vec, (uint8_t*)"\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D"
				"\x01\x01\x01\x05\x00\x03", 16))
		return (do_clear(&vec));
	if (!vecu8_push(&vec, tmp, pem_write_len(tmp, len + 3)))
		return (do_clear(&vec));
	if (!vecu8_push(&vec, (uint8_t*)"\x00\x30", 2))
		return (do_clear(&vec));
	if (!vecu8_push(&vec, tmp, pem_write_len(tmp, len)))
		return (do_clear(&vec));
	if (!write_bignums(&vec, ctx))
		return (do_clear(&vec));
	*dst = (char*)vec.data;
	return (vec.size);
}
