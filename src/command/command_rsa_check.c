/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 13:29:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/14 11:20:50 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	check_dmp(t_rsa_data *data)
{
	t_bignum	one;
	t_bignum	tmp;

	bignum_init(&tmp);
	bignum_init(&one);
	if (!bignum_one(&one) || !bignum_sub(&tmp, data->rsa_ctx.p, &one)
			|| !bignum_mod(&tmp, data->rsa_ctx.d, &tmp))
	{
		ft_putendl_fd("ft_ssl: bignum internal error", 2);
		bignum_clear(&one);
		bignum_clear(&tmp);
		return (0);
	}
	if (bignum_cmp(&tmp, data->rsa_ctx.dmp))
	{
		ft_putendl_fd("ft_ssl: dmp is not equal to d % (p - 1)", 2);
		bignum_clear(&one);
		bignum_clear(&tmp);
		return (0);
	}
	bignum_clear(&one);
	bignum_clear(&tmp);
	return (1);
}

static int	check_dmq(t_rsa_data *data)
{
	t_bignum	one;
	t_bignum	tmp;

	bignum_init(&tmp);
	bignum_init(&one);
	if (!bignum_one(&one) || !bignum_sub(&tmp, data->rsa_ctx.q, &one)
			|| !bignum_mod(&tmp, data->rsa_ctx.d, &tmp))
	{
		ft_putendl_fd("ft_ssl: bignum internal error", 2);
		bignum_clear(&one);
		bignum_clear(&tmp);
		return (0);
	}
	if (bignum_cmp(&tmp, data->rsa_ctx.dmq))
	{
		ft_putendl_fd("ft_ssl: dmq is not equal to d % (q - 1)", 2);
		bignum_clear(&one);
		bignum_clear(&tmp);
		return (0);
	}
	bignum_clear(&one);
	bignum_clear(&tmp);
	return (1);
}

static int	check_coef(t_rsa_data *data)
{
	t_bignum	tmp;

	bignum_init(&tmp);
	if (!bignum_mod_inverse(&tmp, data->rsa_ctx.q, data->rsa_ctx.p))
	{
		ft_putendl_fd("ft_ssl: bignum_mod_inverse failed", 2);
		bignum_clear(&tmp);
		return (0);
	}
	if (bignum_cmp(&tmp, data->rsa_ctx.coef))
	{
		ft_putendl_fd("ft_ssl: coef is not equal to mod_inverse(q, p)", 2);
		bignum_clear(&tmp);
		return (0);
	}
	bignum_clear(&tmp);
	return (1);
}

static int	check2(t_rsa_data *data)
{
	t_bignum	tmp;

	bignum_init(&tmp);
	if (!bignum_mul(&tmp, data->rsa_ctx.p, data->rsa_ctx.q))
	{
		ft_putendl_fd("ft_ssl: bignum_mul failed", 2);
		bignum_clear(&tmp);
		return (0);
	}
	if (bignum_cmp(&tmp, data->rsa_ctx.n))
	{
		ft_putendl_fd("ft_ssl: n is not equal to p * q", 2);
		bignum_clear(&tmp);
		return (0);
	}
	bignum_clear(&tmp);
	if (data->rsa_ctx.dmq && !check_dmq(data))
		return (0);
	if (data->rsa_ctx.dmp && !check_dmp(data))
		return (0);
	if (!check_coef(data))
		return (0);
	return (1);
}

int			cmd_rsa_check(t_rsa_data *data)
{
	if (bignum_is_one(data->rsa_ctx.e))
	{
		ft_putendl_fd("ft_ssl: error: public exponent is one", 2);
		return (0);
	}
	if (!bignum_is_odd(data->rsa_ctx.e))
	{
		ft_putendl_fd("ft_ssl: error: public exponent is even", 2);
		return (0);
	}
	if (data->rsa_ctx.p && (!bignum_is_prime_fasttest(data->rsa_ctx.p)
	|| !bignum_is_prime(data->rsa_ctx.p, BIGNUM_PRIME_CHECKS_AUTO, NULL)))
	{
		ft_putendl_fd("ft_ssl: error: p is not prime", 2);
		return (0);
	}
	if (data->rsa_ctx.q && (!bignum_is_prime_fasttest(data->rsa_ctx.q)
	|| !bignum_is_prime(data->rsa_ctx.q, BIGNUM_PRIME_CHECKS_AUTO, NULL)))
	{
		ft_putendl_fd("ft_ssl: error: q is not prime", 2);
		return (0);
	}
	if (data->rsa_ctx.p && data->rsa_ctx.q && !check2(data))
		return (0);
	return (1);
}
