/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_md4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 15:13:17 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 15:13:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/md4.h"
#include "ft_ssl.h"

int	command_md4(int ac, char **av)
{
	t_hash_data	data;
	t_md4_ctx	ctx;

	data.h.h = &g_hash_md4;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
