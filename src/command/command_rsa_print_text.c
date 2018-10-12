/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa_print_text.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:54:54 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 13:18:32 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_hex(uint8_t val)
{
	if (val >= 10)
		ft_putchar('A' + val);
	else
		ft_putchar('0' + val);
}

static void	do_print_bignum(t_bignum *bignum, char *name)
{
	int		n;
	int		i;

	ft_putstr(name);
	ft_putstr(" (");
	ft_putul(bignum_num_bits(bignum));
	ft_putendl(" bits):");
	n = 0;
	i = bignum_num_bytes(bignum);
	while (i)
	{
		--i;
		print_hex(((uint8_t*)bignum->data)[i] >> 4);
		print_hex(((uint8_t*)bignum->data)[i] & 0xF);
		if (n % 16 == 15)
			ft_putchar('\n');
		else
			ft_putchar(':');
		++n;
	}
	if (n % 16)
		ft_putchar('\n');
}

void		cmd_rsa_print_text(t_rsa_data *data)
{
	if (data->pubin)
	{
		do_print_bignum(data->rsa_ctx.n, "Modulus");
		ft_putstr("Exponent: ");
		bignum_print(data->rsa_ctx.e);
		ft_putstr(" (0x");
		bignum_printhex(data->rsa_ctx.e);
		ft_putendl(")");
	}
	else
	{
		do_print_bignum(data->rsa_ctx.n, "Modulus");
		ft_putstr("Public exponent: ");
		bignum_print(data->rsa_ctx.e);
		ft_putstr(" (0x");
		bignum_printhex(data->rsa_ctx.e);
		ft_putendl(")");
		do_print_bignum(data->rsa_ctx.d, "Private exponent");
		do_print_bignum(data->rsa_ctx.p, "Prime 1");
		do_print_bignum(data->rsa_ctx.q, "Prime 2");
		do_print_bignum(data->rsa_ctx.dmp, "Exponent 1");
		do_print_bignum(data->rsa_ctx.dmq, "Exponent 2");
		do_print_bignum(data->rsa_ctx.coef, "Coefficient");
	}
}
