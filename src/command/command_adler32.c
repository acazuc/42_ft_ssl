/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_adler32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:35:07 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 19:56:59 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/adler32.h"
#include "ft_ssl.h"

int	command_adler32(int ac, char **av)
{
	t_hash_data	data;
	t_adler32_ctx	ctx;

	data.h.hash = &g_hash_adler32;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
