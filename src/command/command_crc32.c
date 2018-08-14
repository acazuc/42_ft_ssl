/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_crc32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:14:02 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 20:14:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/crc32.h"
#include "ft_ssl.h"

int	command_crc32(int ac, char **av)
{
	t_hash_data	data;
	t_crc32_ctx	ctx;

	data.h.h = &g_hash_crc32;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
