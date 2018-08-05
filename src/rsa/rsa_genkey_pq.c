/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_pq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 15:18:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 21:02:39 by acazuc           ###   ########.fr       */
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

static void	do_print_plus(int print, uint32_t n)
{
	uint32_t	i;

	if (!print)
		return;
	i = 0;
	while (i < n)
	{
		ft_putchar('+');
		++i;
	}
}

static int	genprime(t_bignum *r, uint32_t bits, int print)
{
	uint32_t	passed;

	while (1)
	{
		if (!bignum_rand(r, bits, BIGNUM_RAND_TOP_TWO
					, BIGNUM_RAND_BOT_ODD))
			return (0);
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

int		rsa_genkey_pq(t_rsa_ctx *ctx, uint32_t bits, int print)
{
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
