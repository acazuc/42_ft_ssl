/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:27:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 21:02:26 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha1.h"
#include "ft_ssl.h"

int	command_sha1(int ac, char **av)
{
	t_hash_data	data;
	t_sha1_ctx	ctx;

	data.h.h = &g_hash_sha1;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
