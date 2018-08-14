/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bignum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 22:14:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 17:47:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"

static int	do_execute1(int ac, char **av, int (*fn)(t_bignum *r, t_bignum *a, t_bignum *b))
{
	t_bignum	a;
	t_bignum	b;
	t_bignum	r;

	if (ac < 3)
		return (EXIT_FAILURE);
	bignum_init(&a);
	bignum_init(&b);
	bignum_init(&r);
	if (!bignum_dec2bignum(&a, av[0]) || !bignum_dec2bignum(&b, av[2])
			|| !fn(&r, &a, &b) || !bignum_print(&r))
	{
		bignum_clear(&a);
		bignum_clear(&b);
		bignum_clear(&r);
		return (EXIT_FAILURE);
	}
	bignum_clear(&a);
	bignum_clear(&b);
	bignum_clear(&r);
	return (EXIT_SUCCESS);
}

static int	do_execute2(int ac, char **av, int (*fn)(t_bignum *r, t_bignum *a, uint32_t b))
{
	t_bignum	a;
	t_bignum	r;
	uint64_t	b;

	if (ac < 3)
		return (EXIT_FAILURE);
	bignum_init(&a);
	b = ft_atol(av[2]);
	bignum_init(&r);
	if (!bignum_dec2bignum(&a, av[0]) || !fn(&r, &a, b) || !bignum_print(&r))
	{
		bignum_clear(&a);
		bignum_clear(&r);
		return (EXIT_FAILURE);
	}
	bignum_clear(&a);
	bignum_clear(&r);
	return (EXIT_SUCCESS);
}

static int	do_execute3(int ac, char **av, int (*fn)(t_bignum *r, t_bignum *a))
{
	t_bignum	a;
	t_bignum	r;

	if (ac < 2)
		return (EXIT_FAILURE);
	bignum_init(&a);
	bignum_init(&r);
	if (!bignum_dec2bignum(&a, av[0]) || !fn(&r, &a) || !bignum_print(&r))
	{
		bignum_clear(&a);
		bignum_clear(&r);
		return (EXIT_FAILURE);
	}
	bignum_clear(&a);
	bignum_clear(&r);
	return (EXIT_SUCCESS);
}

static int	do_execute_prime(char *v)
{
	t_bignum	a;
	int		is_prime;

	bignum_init(&a);
	if (!bignum_dec2bignum(&a, v))
	{
		bignum_clear(&a);
		return (EXIT_FAILURE);
	}
	is_prime = bignum_is_prime(&a, BIGNUM_PRIME_CHECKS_AUTO, NULL);
	if (is_prime == -1)
	{
		bignum_clear(&a);
		return (EXIT_FAILURE);
	}
	if (is_prime)
		ft_putchar('1');
	else
		ft_putchar('0');
	bignum_clear(&a);
	return (EXIT_SUCCESS);
}

int	command_bignum(int ac, char **av)
{
	if (ac < 2)
		return (EXIT_FAILURE);
	if (!ft_strcmp(av[1], "+"))
		return (do_execute1(ac, av, &bignum_add));
	if (!ft_strcmp(av[1], "-"))
		return (do_execute1(ac, av, &bignum_sub));
	if (!ft_strcmp(av[1], "*"))
		return (do_execute1(ac, av, &bignum_mul));
	if (!ft_strcmp(av[1], "/"))
		return (do_execute1(ac, av, &bignum_div));
	if (!ft_strcmp(av[1], "%"))
		return (do_execute1(ac, av, &bignum_mod));
	if (!ft_strcmp(av[1], "^"))
		return (do_execute1(ac, av, &bignum_exp));
	if (!ft_strcmp(av[1], ">>"))
		return (do_execute2(ac, av, &bignum_rshift));
	if (!ft_strcmp(av[1], "<<"))
		return (do_execute2(ac, av, &bignum_lshift));
	if (!ft_strcmp(av[1], ">>1"))
		return (do_execute3(ac, av, &bignum_rshift1));
	if (!ft_strcmp(av[1], "<<1"))
		return (do_execute3(ac, av, &bignum_lshift1));
	if (!ft_strcmp(av[1], "is_prime"))
		return (do_execute_prime(av[0]));
	return (EXIT_FAILURE);
}
