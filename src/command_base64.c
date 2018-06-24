/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_base64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:30:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/23 23:49:53 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

static void	callback(uint8_t *data, size_t len, void *userptr)
{
	int osef;
	
	osef = write(*(int*)userptr, data, len);
	(void)osef;
}

int		command_base64(int ac, char **av)
{
	t_b64e_ctx	ctx;
	uint8_t		buffer[4096];
	int		readed;
	int		fd;

	fd = 1;
	if (!b64e_init(&ctx, callback, &fd))
		return (EXIT_FAILURE);
	while ((readed = read(0, buffer, 4096)) > 0)
	{
		b64e_update(&ctx, buffer, readed);
	}
	if (readed < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
