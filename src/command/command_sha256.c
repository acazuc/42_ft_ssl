/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha256.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:27:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 14:25:05 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha256.h"
#include "ft_ssl.h"

int	command_sha256(int ac, char **av)
{
	t_hash_data		data;
	t_sha256_ctx	ctx;

	data.h.hash = &g_hash_sha256;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
