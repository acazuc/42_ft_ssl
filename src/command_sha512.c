/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_sha512.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 09:31:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 17:40:07 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha512.h"

int	command_sha512(int ac, char **av)
{
	t_hash_data	data;
	t_sha512_ctx	ctx;

	data.ctx = &ctx;
	data.digest_size = 64;
	data.hash_name = "SHA512";
	data.init = (t_hash_init*)&sha512_init;
	data.update = (t_hash_update*)&sha512_update;
	data.final = (t_hash_final*)&sha512_final;
	return (command_hash(ac, av, &data));
}
