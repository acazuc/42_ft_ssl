/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:45:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 12:01:59 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

int	des_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	dprintf(2, "decrypt_init: %lx\n", key);
	des_generate_keys(ctx, key);
	ctx->mode = 1;
	return (1);
}

int	des_decrypt_update(t_des_ctx *ctx, uint64_t *data, size_t len)
{
	dprintf(2, "decrypt_update\n");
	*data = ft_swap_ulong(*data);
	des_operate_block(ctx, data);
	*data = ft_swap_ulong(*data);
	if (ctx->callback)
		return (ctx->callback(ctx->userptr, data, len));
	return (1);
}

int	des_decrypt_final(t_des_ctx *ctx)
{
	(void)ctx;
	return (1);
}
