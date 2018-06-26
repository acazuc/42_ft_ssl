/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha224.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:54:19 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:19:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha224.h"

int	command_sha224(int ac, char **av)
{
	t_hash_data	data;
	t_sha224_ctx	ctx;

	data.h.h = &g_hash_sha224;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
