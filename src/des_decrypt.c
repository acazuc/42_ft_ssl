/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:45:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 16:16:41 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		des_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	des_generate_keys(ctx, key);
	ctx->buff_len = 0;
	ctx->tmp_len = 0;
	ctx->mode = 1;
	if (!(ctx->buff = malloc(DES_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	return (1);
}

static int	execute_callback(t_des_ctx *ctx)
{
	int	ret;

	ret = ctx->callback(ctx->userptr, ctx->buff, ctx->buff_len);
	ctx->buff_len = 0;
	if (!ret)
		return (0);
	return (1);
}

int		des_decrypt_update(t_des_ctx *ctx, const uint8_t *data, size_t len)
{
	while (ctx->tmp_len + len >= 9)
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
		if ((ctx->buff_len += 8) >= DES_BUFF_LEN - 8 && !execute_callback(ctx))
			return (0);
	}
	while (len--)
		ctx->tmp[ctx->tmp_len++] = *(data++);
	if (ctx->buff_len && !execute_callback(ctx))
		return (0);
	return (1);
}

int		des_decrypt_final(t_des_ctx *ctx)
{
	free(ctx->buff);
	if (!ctx->tmp_len)
		return (1);
	if (ctx->nopad)
	{
		*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
		ctx->pre_mod(ctx, (uint64_t*)ctx->tmp);
		des_operate_block(ctx, (uint64_t*)ctx->tmp);
		ctx->post_mod(ctx, (uint64_t*)ctx->tmp);
		*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
		return (ctx->callback(ctx->userptr, ctx->tmp, ctx->tmp_len));
	}
	if (ctx->tmp_len != 8)
		return (0);
	*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
	ctx->pre_mod(ctx, (uint64_t*)ctx->tmp);
	des_operate_block(ctx, (uint64_t*)ctx->tmp);
	ctx->post_mod(ctx, (uint64_t*)ctx->tmp);
	*(uint64_t*)ctx->tmp = ft_swap_ulong(*(uint64_t*)ctx->tmp);
	if (ctx->tmp[7] > 8)
		return (0);
	if (ctx->tmp[7] != 8)
		return (ctx->callback(ctx->userptr, ctx->tmp, 8 - ctx->tmp[7]));
	return (1);
}
