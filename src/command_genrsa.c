/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 19:56:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 15:55:31 by acazuc           ###   ########.fr       */
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
	if (!rsa_genkey(&ctx, len, 1))
		return (EXIT_FAILURE);
	ft_putstr("e is ");
	bignum_print(ctx.e);
	ft_putstr(" (0x");
	bignum_printhex(ctx.e);
	ft_putendl(")");
	return (1);
}
