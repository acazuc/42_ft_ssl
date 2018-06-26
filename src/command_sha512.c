/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha512.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 09:31:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:19:46 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

int	command_sha512(int ac, char **av)
{
	t_hash_data	data;
	t_sha512_ctx	ctx;

	data.h.h = &g_hash_sha512;
	data.h.ctx = &ctx;
	return (command_hash(ac, av, &data));
}
