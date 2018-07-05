/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:03:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 13:54:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	des_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	des_generate_keys(ctx, key);
	return (1);
}

int	des_encrypt_update(t_des_ctx *ctx, uint64_t *data, size_t len)
{
	(void)len;
	des_operate_block(ctx, data, 0);
	return (1);
}

int	des_encrypt_final(t_des_ctx *ctx)
{
	(void)ctx;
	return (1);
}
