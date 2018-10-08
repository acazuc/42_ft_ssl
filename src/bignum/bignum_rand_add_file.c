/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand_add_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:53:17 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:54:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <unistd.h>
#include <fcntl.h>

int	bignum_rand_add_file(char *file)
{
	ssize_t	readed;
	ssize_t	tmp;
	char	buf[2048];
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if ((readed = read(fd, buf, 2048)) < 0)
	{
		close(fd);
		return (0);
	}
	tmp = 0;
	while (readed - tmp > 8)
	{
		bignum_rand_add(*(uint64_t*)&(buf[tmp]));
		tmp += 8;
	}
	while (tmp < readed)
	{
		bignum_rand_add(buf[tmp]);
		++tmp;
	}
	close(fd);
	return (1);
}
