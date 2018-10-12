/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 21:28:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 12:04:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_init(t_rsautl_data *data, int ac, char **av)
{
	data->fdin = 0;
	data->fdout = 1;
	data->keyfd = -1;
	data->pubin = 0;
	data->mode = -1;
	data->hexdump = 0;
	data->passin = NULL;
	if (!cmd_rsautl_args(data, ac, av))
		return (0);
	return (1);
}

int			command_rsautl(int ac, char **av)
{
	t_rsautl_data	data;

	if (!do_init(&data, ac, av))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
