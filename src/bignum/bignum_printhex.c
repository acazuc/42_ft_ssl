/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_printhex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 23:15:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 23:17:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

int	bignum_printhex_fd(t_bignum *bignum, int fd)
{
	(void)bignum;
	(void)fd;
	return (1);
}

int	bignum_printhex(t_bignum *bignum)
{
	return (bignum_printhex_fd(bignum, 1));
}
