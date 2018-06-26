/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha256.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:27:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:19:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

int	command_sha256(int ac, char **av)
{
	t_hash_data	data;
	t_sha256_ctx	ctx;

	data.h.h = &g_hash_sha256;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
