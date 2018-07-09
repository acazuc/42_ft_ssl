/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 22:15:49 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "rsa.h"

int	command_genrsa(int ac, char **av)
{
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
