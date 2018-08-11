/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aes_128.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:38:42 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 16:49:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

int	command_aes_128(int ac, char **av, t_aes_data *data)
{
	t_aes_ctx	ctx;
	uint8_t		key[24];
	uint8_t		block[32] = {0xdb, 0x13, 0x53, 0x45, 0xf2, 0x0a, 0x22, 0x5c, 0x01, 0x01, 0x01, 0x01, 0xc6, 0xc6, 0xc6, 0xc6, 0xd4, 0xd4, 0xd4, 0xd5, 0x2d, 0x26, 0x31, 0x4c};

	ft_memset(&ctx, 0, sizeof(ctx));
	ft_memset(key, 0x00, sizeof(key));
	aes_encrypt_init(&ctx, key, 24);
	ft_memcpy(block, "saluttoutlemonde", 16);
	//aes_mixcolumns(block);
	aes_encrypt_update(&ctx, block, 16);
	for (uint8_t i = 0; i < 16; ++i)
		printf("%02x ", block[i]);
	printf("\n");
	(void)ac;
	(void)av;
	(void)data;
	return (EXIT_SUCCESS);
}
