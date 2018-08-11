/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha224.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:54:19 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:02:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha224.h"
#include "ft_ssl.h"

int	command_sha224(int ac, char **av)
{
	t_hash_data	data;
	t_sha224_ctx	ctx;

	data.h.h = &g_hash_sha224;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
