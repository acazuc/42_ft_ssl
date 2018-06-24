/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha224.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:54:19 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 17:39:48 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha224.h"

int	command_sha224(int ac, char **av)
{
	t_hash_data	data;
	t_sha224_ctx	ctx;

	data.ctx = &ctx;
	data.digest_size = 28;
	data.hash_name = "SHA224";
	data.init = (t_hash_init*)&sha224_init;
	data.update = (t_hash_update*)&sha224_update;
	data.final = (t_hash_final*)&sha224_final;
	return (command_hash(ac, av, &data));
}
