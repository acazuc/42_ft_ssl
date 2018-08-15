/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ripemd128.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 13:16:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 13:17:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/ripemd128.h"
#include "ft_ssl.h"

int	command_ripemd128(int ac, char **av)
{
	t_hash_data	data;
	t_ripemd128_ctx	ctx;

	data.h.h = &g_hash_ripemd128;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
