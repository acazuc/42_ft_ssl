/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 22:59:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"

int	command_genrsa(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_bignum *a = bignum_new();
	bignum_dec2bignum(a, "112233445566778899112233445566778899");
	//bignum_dec2bignum(a, "32416190071");
	ft_putstr("is_prime: ");
	ft_putnbr(bignum_is_prime(a, BIGNUM_PRIME_CHECKS_AUTO));
	ft_putchar('\n');
	t_bignum *b = bignum_new();
	bignum_dec2bignum(b, "8104047463");
	//bignum_grow(b, 2);
	//bignum_grow(b, 44152263);
	//bignum_grow(b, 41152263);
	t_bignum *c = bignum_new();
	bignum_dec2bignum(c, "32416189853");
	bignum_mod_exp(c, a, b, c);
	bignum_print(a);
	ft_putchar('/');
	bignum_print(b);
	ft_putchar('=');
	bignum_print(c);
	ft_putchar('\n');
	return (1);
}
