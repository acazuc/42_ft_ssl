/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 10:07:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 10:19:30 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <fcntl.h>

int	bignum_rand(t_bignum *bignum, uint64_t bits)
{
	int	fd;

	if (!bignum_resize(bignum, bits / sizeof(*bignum->data)))
		return (0);
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (0);
	if (read(fd, bignum->data, bits / 8) != (int64_t)bits / 8)
		return (0);
	close(fd);
	return (1);
}
