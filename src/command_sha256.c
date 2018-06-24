/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha256.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:27:37 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 17:39:55 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

int	command_sha256(int ac, char **av)
{
	t_hash_data	data;
	t_sha256_ctx	ctx;

	data.ctx = &ctx;
	data.digest_size = 32;
	data.hash_name = "SHA256";
	data.init = (t_hash_init*)&sha256_init;
	data.update = (t_hash_update*)&sha256_update;
	data.final = (t_hash_final*)&sha256_final;
	return (command_hash(ac, av, &data));
}
