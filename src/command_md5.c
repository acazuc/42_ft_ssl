/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:26:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 20:11:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int	command_md5(int ac, char **av)
{
	t_hash_data	data;
	t_md5_ctx	ctx;

	data.h.h = &g_hash_md5;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
