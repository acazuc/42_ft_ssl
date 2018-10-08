/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ripemd256.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:03:56 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 14:24:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/ripemd256.h"
#include "ft_ssl.h"

int	command_ripemd256(int ac, char **av)
{
	t_hash_data		data;
	t_ripemd256_ctx	ctx;

	data.h.hash = &g_hash_ripemd256;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
