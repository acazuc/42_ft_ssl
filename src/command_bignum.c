/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bignum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 22:14:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 17:31:02 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"

static int	do_execute1(char *v1, char *v2, int (*fn)(t_bignum *r, t_bignum *a, t_bignum *b))
{
	t_bignum	*a;
	t_bignum	*b;
	t_bignum	*r;

	if (!(a = bignum_new()))
		return (EXIT_FAILURE);
	if (!(b = bignum_new()))
		return (EXIT_FAILURE);
	if (!(r = bignum_new()))
		return (EXIT_FAILURE);
	if (!bignum_dec2bignum(a, v1))
		return (EXIT_FAILURE);
	if (!bignum_dec2bignum(b, v2))
		return (EXIT_FAILURE);
	/*ft_putstr("a: ");
	bignum_print(a);
	ft_putchar('\n');
	ft_putstr("b: ");
	bignum_print(b);
	ft_putchar('\n');*/
	if (!fn(r, a, b))
		return (EXIT_FAILURE);
	if (!bignum_print(r))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	do_execute2(char *v1, char *v2, int (*fn)(t_bignum *r, t_bignum *a, uint64_t b))
{
	t_bignum	*a;
	t_bignum	*r;
	uint64_t	b;

	if (!(a = bignum_new()))
		return (EXIT_FAILURE);
	b = ft_atol(v2);
	if (!(r = bignum_new()))
		return (EXIT_FAILURE);
	if (!bignum_dec2bignum(a, v1))
		return (EXIT_FAILURE);
	if (!fn(r, a, b))
		return (EXIT_FAILURE);
	if (!bignum_print(r))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	do_execute3(char *v1, int (*fn)(t_bignum *r, t_bignum *a))
{
	t_bignum	*a;
	t_bignum	*r;

	if (!(a = bignum_new()))
		return (EXIT_FAILURE);
	if (!(r = bignum_new()))
		return (EXIT_FAILURE);
	if (!bignum_dec2bignum(a, v1))
		return (EXIT_FAILURE);
	if (!fn(r, a))
		return (EXIT_FAILURE);
	if (!bignum_print(r))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	do_execute_prime(char *v)
{
	t_bignum	*a;
	int		is_prime;

	if (!(a = bignum_new()))
		return (EXIT_FAILURE);
	if (!bignum_dec2bignum(a, v))
		return (EXIT_FAILURE);
	is_prime = bignum_is_prime(a, BIGNUM_PRIME_CHECKS_AUTO);
	if (is_prime == -1)
		return (EXIT_FAILURE);
	if (is_prime)
		ft_putchar('1');
	else
		ft_putchar('0');
	return (EXIT_SUCCESS);
}

int	command_bignum(int ac, char **av)
{
	if (ac != 3)
		return (EXIT_FAILURE);
	if (!ft_strcmp(av[1], "+"))
		return (do_execute1(av[0], av[2], &bignum_add));
	if (!ft_strcmp(av[1], "-"))
		return (do_execute1(av[0], av[2], &bignum_sub));
	if (!ft_strcmp(av[1], "*"))
		return (do_execute1(av[0], av[2], &bignum_mul));
	if (!ft_strcmp(av[1], "/"))
		return (do_execute1(av[0], av[2], &bignum_div));
	if (!ft_strcmp(av[1], "%"))
		return (do_execute1(av[0], av[2], &bignum_mod));
	if (!ft_strcmp(av[1], "^"))
		return (do_execute1(av[0], av[2], &bignum_exp));
	if (!ft_strcmp(av[1], ">>"))
		return (do_execute2(av[0], av[2], &bignum_rshift));
	if (!ft_strcmp(av[1], "<<"))
		return (do_execute2(av[0], av[2], &bignum_lshift));
	if (!ft_strcmp(av[1], ">>1"))
		return (do_execute3(av[0], &bignum_rshift1));
	if (!ft_strcmp(av[1], "<<1"))
		return (do_execute3(av[0], &bignum_lshift1));
	if (!ft_strcmp(av[1], "is_prime"))
		return (do_execute_prime(av[0]));
	return (EXIT_FAILURE);
}
