/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_pq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 15:18:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 18:20:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

static int	do_clear(t_rsa_ctx *ctx)
{
	bignum_free(ctx->p);
	bignum_free(ctx->q);
	return (0);
}

static void	do_print_plus(int print, uint64_t n)
{
	uint64_t	i;

	if (!print)
		return;
	i = 0;
	while (i < n)
	{
		ft_putchar('+');
		++i;
	}
}

static int	genprime(t_bignum *r, uint64_t bits, int print)
{
	uint64_t	passed;

	while (1)
	{
		if (!bignum_rand(r, bits))
			return (0);
		r->data[0] |= 1;
		r->data[bits / sizeof(*r->data) / 8] |= 1
			<< (1 - (bits % (8 * sizeof(*r->data))));
		if (!bignum_is_prime_fasttest(r))
			continue;
		if (print)
			ft_putchar('.');
		if (bignum_is_prime(r, BIGNUM_PRIME_CHECKS_AUTO, &passed) == 1)
		{
			do_print_plus(print, passed);
			break;
		}
		do_print_plus(print, passed);
	}
	if (print)
		ft_putchar('\n');
	return (1);
}

int		rsa_genkey_pq(t_rsa_ctx *ctx, uint64_t bits, int print)
{
	ctx->p = NULL;
	ctx->q = NULL;
	if (!(ctx->p = bignum_new()))
		return (do_clear(ctx));
	if (!genprime(ctx->p, (bits + 1) / 2, print))
		return (do_clear(ctx));
	if (!(ctx->q = bignum_new()))
		return (do_clear(ctx));
	while (1)
	{
		if (!genprime(ctx->q, bits - (bits + 1) / 2, print))
			return (do_clear(ctx));
		if (bignum_cmp(ctx->p, ctx->q))
			break;
	}
	return (1);
}
