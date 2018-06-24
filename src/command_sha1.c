/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:27:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 17:39:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha1.h"

int	command_sha1(int ac, char **av)
{
	t_hash_data	data;
	t_sha1_ctx	ctx;

	data.ctx = &ctx;
	data.digest_size = 20;
	data.hash_name = "SHA1";
	data.init = (t_hash_init*)&sha1_init;
	data.update = (t_hash_update*)&sha1_update;
	data.final = (t_hash_final*)&sha1_final;
	return (command_hash(ac, av, &data));
}
