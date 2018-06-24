/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:26:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 17:39:32 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int	command_md5(int ac, char **av)
{
	t_hash_data	data;
	t_md5_ctx	ctx;

	data.ctx = &ctx;
	data.digest_size = 16;
	data.hash_name = "MD5";
	data.init = (t_hash_init*)&md5_init;
	data.update = (t_hash_update*)&md5_update;
	data.final = (t_hash_final*)&md5_final;
	return (command_hash(ac, av, &data));
}
