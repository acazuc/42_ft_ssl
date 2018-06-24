/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:30:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 12:25:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include <stdio.h>

static void	callback(uint8_t *data, size_t len, void *userptr)
{
	t_b64e_data	*ptr;
	int		osef;
	int		tmp;
	
	ptr = (t_b64e_data*)userptr;
	while (ptr->count + len >= 64)
	{
		tmp = 64 - ptr->count;
		if (tmp > 64)
			tmp = 64;
		osef = write(ptr->fd, data, tmp);
		data += tmp;
		len -= tmp;
		ptr->count = 0;
		ft_putchar('\n');
	}
	ptr->count += len;
	osef = write(ptr->fd, data, len);
	(void)osef;
}

int		command_base64(int ac, char **av)
{
	t_b64e_data	data;
	t_b64e_ctx	ctx;
	uint8_t		buffer[409];
	int		readed;
	int		fd;

	fd = 1;
	data.fd = fd;
	data.count = 0;
	if (!b64e_init(&ctx, callback, &data))
		return (EXIT_FAILURE);
	while ((readed = read(0, buffer, 409)) > 0)
	{
		b64e_update(&ctx, buffer, readed);
	}
	if (readed < 0)
		return (EXIT_FAILURE);
	b64e_finish(&ctx);
	if (data.count)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
