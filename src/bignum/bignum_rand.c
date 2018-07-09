/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 10:07:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 15:11:56 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <fcntl.h>

int	bignum_rand(t_bignum *bignum, uint64_t bits)
{
	uint64_t	i;
	int		fd;

	if (!bits)
		bits = 1;
	if (!bignum_resize(bignum, bits / 8 / sizeof(*bignum->data) == 0 ? 1 : bits / 8 / sizeof(*bignum->data)))
		return (0);
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (0);
	if (read(fd, bignum->data, bits / 8) != (int64_t)bits / 8)
	{
		close(fd);
		return (0);
	}
	close(fd);
	i = 0;
	while (i < bignum->len)
		bignum->data[i++] %= BIGNUM_BASE;
	return (1);
}
