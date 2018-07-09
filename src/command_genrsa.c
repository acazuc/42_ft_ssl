/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 20:49:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int	command_genrsa(int ac, char **av)
{
	/*t_bignum *a = bignum_new();
	bignum_dec2bignum(a, "1269343521640258108984378929387367856567447047363750913089043745155208");
	bignum_rshift1(a, a);
	ft_putstr("a: ");
	bignum_print(a);
	ft_putstr("\nah: ");
	bignum_printhex(a);
	ft_putchar('\n');
	t_bignum *b = bignum_new();
	bignum_dec2bignum(b, "10");
	t_bignum *c = bignum_new();
	bignum_div(c, a, b);
	ft_putstr("c: ");
	bignum_print(c);
	ft_putstr("\nch: ");
	bignum_printhex(c);
	ft_putchar('\n');
	return (0);
	(void)ac;
	(void)av;*/
	/*t_bignum *b = bignum_new();
	bignum_dec2bignum(b, "4722366482869645213696");
	ft_putul(b->data[0]);
	ft_putchar('\n');
	ft_putstr("a: ");
	bignum_printhex(a);
	ft_putchar('\n');
	ft_putstr("b: ");
	bignum_printhex(b);
	ft_putchar('\n');
	t_bignum *c = bignum_new();
	t_bignum *d = bignum_new();
	bignum_div_mod(c, d, a, b);
	ft_putstr("a: ");
	bignum_printhex(a);
	ft_putchar('\n');
	ft_putstr("b: ");
	bignum_printhex(b);
	ft_putchar('\n');
	ft_putstr("c: ");
	bignum_printhex(c);
	ft_putchar('\n');
	ft_putstr("d: ");
	bignum_printhex(d);
	ft_putchar('\n');
	(void)ac;
	(void)av;
	return (0);*/
	t_rsa_ctx	ctx;
	uint64_t	len;

	len = 512;
	if (ac)
		len = ft_atol(av[0]);
	if (len < 16)
	{
		ft_putendl_fd("ft_ssl: invalid key len, minimum is 16", 2);
		return (EXIT_FAILURE);
	}
	if (!rsa_genkey(&ctx, len, 1))
	{
		ft_putendl_fd("ft_ssl: failed to generate key", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr("e is ");
	bignum_print(ctx.e);
	ft_putstr(" (0x");
	bignum_printhex(ctx.e);
	ft_putendl(")");
	ft_putstr("p: ");
	bignum_print(ctx.p);
	ft_putchar('\n');
	ft_putstr("q: ");
	bignum_print(ctx.q);
	ft_putchar('\n');
	t_bignum *a = bignum_new();
	bignum_dec2bignum(a, "112233445566778899112233445566778899887766554433211");
	bignum_mod_exp(a, a, ctx.e, ctx.n);
	ft_putstr("Crypted: ");
	bignum_print(a);
	ft_putchar('\n');
	bignum_mod_exp(a, a, ctx.d, ctx.n);
	ft_putstr("Decrypted: ");
	bignum_print(a);
	ft_putchar('\n');
	return (1);
}
