/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ripemd160.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:35:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/14 21:35:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/ripemd160.h"
#include "ft_ssl.h"

int	command_ripemd160(int ac, char **av)
{
	t_hash_data	data;
	t_ripemd160_ctx	ctx;

	data.h.h = &g_hash_ripemd160;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
