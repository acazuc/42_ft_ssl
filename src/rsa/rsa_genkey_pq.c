/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_genkey_pq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 15:18:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 17:59:02 by acazuc           ###   ########.fr       */
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
		return ;
	i = 0;
	while (i < n)
	{
		ft_putchar_fd('+', 2);
		++i;
	}
}

static int	genprime(t_bignum *r, t_bignum *e, uint32_t bits, int print)
{
	t_bignum	one;
	t_bignum	tmp;
	int		ret;
	uint32_t	passed;

	bignum_init(&tmp);
	bignum_init(&one);
	if (!bignum_one(&one))
		return (0);
	ret = 0;
	while (1)
	{
		if (!bignum_rand(r, bits, BIGNUM_RAND_TOP_TWO
					, BIGNUM_RAND_BOT_ODD)
				||!bignum_sub(&tmp, r, &one)
				|| !bignum_gcd(&tmp, &tmp, e))
			break ;
		if (!bignum_is_word(&tmp, 1) || !bignum_is_prime_fasttest(r))
			continue ;
		if (print)
			ft_putchar_fd('.', 2);
		if (bignum_is_prime(r, BIGNUM_PRIME_CHECKS_AUTO, &passed) == 1)
		{
			do_print_plus(print, passed);
			ret = 1;
			break ;
		}
		do_print_plus(print, passed);
	}
	bignum_clear(&tmp);
	bignum_clear(&one);
	return (ret);
}

int			rsa_genkey_pq(t_rsa_ctx *ctx, uint32_t bits, int print)
{
	if (!(ctx->p = bignum_new()))
		return (do_clear(ctx));
	if (!genprime(ctx->p, ctx->e, (bits + 1) / 2, print))
		return (do_clear(ctx));
	if (print)
		ft_putchar_fd('\n', 2);
	if (!(ctx->q = bignum_new()))
		return (do_clear(ctx));
	while (1)
	{
		if (!genprime(ctx->q, ctx->e, bits - (bits + 1) / 2, print))
			return (do_clear(ctx));
		if (bignum_cmp(ctx->p, ctx->q))
			break ;
	}
	if (print)
		ft_putchar_fd('\n', 2);
	return (1);
}
