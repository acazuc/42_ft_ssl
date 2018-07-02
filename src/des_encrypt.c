/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:03:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/02 21:07:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

int	des_encrypt_init(t_des_ctx *ctx, uint64_t key)
{
	des_generate_keys(ctx, key);
	ctx->buff_len = 0;
	ctx->tmp_len = 0;
	ctx->mode = 0;
	if (!(ctx->buff = malloc(DES_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	return (1);
}

int	des_encrypt_update(t_des_ctx *ctx, const uint8_t *data, size_t len)
{
	ctx->buff_len = 0;
	while (ctx->tmp_len + len >= 8)
	{
		ft_memcpy(ctx->tmp + ctx->tmp_len, data, 8 - ctx->tmp_len);
		data += 8 - ctx->tmp_len;
		len -= 8 - ctx->tmp_len;
		ctx->tmp_len = 0;
		*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
		ctx->pre_mod(ctx, (uint64_t*)ctx->tmp);
		des_operate_block(ctx, (uint64_t*)ctx->tmp);
		ctx->post_mod(ctx, (uint64_t*)ctx->tmp);
		*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
		ft_memcpy(ctx->buff + ctx->buff_len, ctx->tmp, 8);
		if ((ctx->buff_len += 8) >= DES_BUFF_LEN - 8)
		{
			ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
			ctx->buff_len = 0;
		}
	}
	while (len--)
		ctx->tmp[ctx->tmp_len++] = *(data++);
	if (ctx->buff_len)
		ctx->callback(ctx->buff, ctx->buff_len, ctx->userptr);
	return (1);
}

int	des_encrypt_final(t_des_ctx *ctx)
{
	uint8_t	padding;
	uint8_t	tmp[8];
	int	i;

	free(ctx->buff);
	if (ctx->nopad)
	{
		if (!ctx->tmp_len)
			return (1);
		*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
		ctx->pre_mod(ctx, (uint64_t*)ctx->tmp);
		des_operate_block(ctx, (uint64_t*)ctx->tmp);
		ctx->post_mod(ctx, (uint64_t*)ctx->tmp);
		*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
		ctx->callback(ctx->tmp, ctx->tmp_len, ctx->userptr);
	}
	else
	{
		padding = 8 - ctx->tmp_len;
		i = 0;
		while (i < padding)
			tmp[i++] = padding;
		des_encrypt_update(ctx, tmp, padding);
	}
	return (1);
}
