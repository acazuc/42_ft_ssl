/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_md2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:30:52 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 17:30:59 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/md2.h"
#include "ft_ssl.h"

int	command_md2(int ac, char **av)
{
	t_hash_data	data;
	t_md2_ctx	ctx;

	data.h.hash = &g_hash_md2;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
