/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 18:17:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/25 22:20:52 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

int	random_bytes(uint8_t *dst, int len)
{
	int	fd;

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (0);
	if (read(fd, dst, len) != len)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
