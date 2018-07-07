/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bignum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 22:14:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 22:44:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"

static int	do_execute(char *v1, char *v2, int (*fn)(t_bignum *r, t_bignum *a, t_bignum *b))
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
	if (!fn(r, a, b))
		return (EXIT_FAILURE);
	if (!bignum_print(r))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	command_bignum(int ac, char **av)
{
	if (ac != 3)
		return (EXIT_FAILURE);
	if (av[1][0] == '+')
		return (do_execute(av[0], av[2], &bignum_add));
	if (av[1][0] == '-')
		return (do_execute(av[0], av[2], &bignum_sub));
	if (av[1][0] == '*')
		return (do_execute(av[0], av[2], &bignum_mul));
	if (av[1][0] == '/')
		return (do_execute(av[0], av[2], &bignum_div));
	if (av[1][0] == '%')
		return (do_execute(av[0], av[2], &bignum_mod));
	return (EXIT_FAILURE);
}
