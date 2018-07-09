/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 10:07:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/09 16:35:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <fcntl.h>

int	bignum_rand(t_bignum *bignum, uint64_t bits)
{
	uint64_t	i;
	int		fd;

	if (!bits)
	{
		bignum_zero(bignum);
		return (1);
	}
	if (!bignum_resize(bignum, bits + (8 * sizeof(*bignum->data) - 1)
				/ 8 / sizeof(*bignum->data)))
		return (0);
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (0);
	if (read(fd, bignum->data, bits / 8) != (int64_t)bits / 8)
	{
		close(fd);
		return (0);
	}
	ft_memset((char*)bignum->data + bits / 8, 0
			, bignum->len * sizeof(*bignum->data) - bits / 8);
	close(fd);
	i = 0;
	while (i < bignum->len)
		bignum->data[i++] %= BIGNUM_BASE;
	return (1);
}
