/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha384.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:48:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 14:25:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha384.h"
#include "ft_ssl.h"

int	command_sha384(int ac, char **av)
{
	t_hash_data		data;
	t_sha384_ctx	ctx;

	data.h.hash = &g_hash_sha384;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
