/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha384.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:48:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:19:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha384.h"

int	command_sha384(int ac, char **av)
{
	t_hash_data	data;
	t_sha384_ctx	ctx;

	data.h.h = &g_hash_sha384;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
