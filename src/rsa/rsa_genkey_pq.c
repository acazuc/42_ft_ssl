/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_pq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 15:18:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 15:49:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static int	genprime(t_bignum *r, uint64_t bits, int print)
{
	uint64_t	passed;

	while (1)
	{
		if (!bignum_rand(r, bits))
			return (0);
		r->data[0] |= 1;
		r->data[bits / sizeof(*r->data) / 8] |= 1 << (bits % (8 * sizeof(*r->data)));
		if (!bignum_is_prime_fasttest(r))
			continue;
		if (print)
			ft_putchar('.');
		if (bignum_is_prime(r, BIGNUM_PRIME_CHECKS_AUTO, &passed) == 1)
		{
			if (print)
				for (uint64_t i = 0; i < passed; ++i)
					ft_putchar('+');
			break;
		}
	}
	if (print)
		ft_putchar('\n');
	return (1);
}

int		rsa_genkey_pq(t_rsa_ctx *ctx, uint64_t bits, int print)
{
	if (!(ctx->p = bignum_new()))
		return (0);
	if (!genprime(ctx->p, (bits + 1) / 2, print))
	{
		bignum_free(ctx->p);
		return (0);
	}
	if (!(ctx->q = bignum_new()))
	{
		bignum_free(ctx->p);
		return (0);
	}
	if (!genprime(ctx->q, (bits + 1) / 2, print))
	{
		bignum_free(ctx->q);
		bignum_free(ctx->p);
		return (0);
	}
	return (1);
}
