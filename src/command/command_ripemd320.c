/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ripemd320.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 14:33:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 14:33:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/ripemd320.h"
#include "ft_ssl.h"

int	command_ripemd320(int ac, char **av)
{
	t_hash_data	data;
	t_ripemd320_ctx	ctx;

	data.h.h = &g_hash_ripemd320;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
