/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha384.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:48:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 17:40:02 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha384.h"

int	command_sha384(int ac, char **av)
{
	t_hash_data	data;
	t_sha384_ctx	ctx;

	data.ctx = &ctx;
	data.digest_size = 48;
	data.hash_name = "SHA384";
	data.init = (t_hash_init*)&sha384_init;
	data.update = (t_hash_update*)&sha384_update;
	data.final = (t_hash_final*)&sha384_final;
	return (command_hash(ac, av, &data));
}
