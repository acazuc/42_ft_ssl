/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:45:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 22:52:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

int	des_decore_init(t_des_ctx *ctx, t_des_mode mode, uint64_t key
		, t_des_callback callback, void *userptr)
{
	des_generate_keys(ctx, key);
	ctx->callback = callback;
	ctx->userptr = userptr;
	ctx->block_mode = mode;
	ctx->mode = 1;
	if (!(ctx->buff = malloc(DES_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	return (1);
}

int	des_decode_update(t_des_ctx *ctx, const uint8_t *data, size_t len)
{
	uint64_t	tmp;

	ctx->buff_len = 0;
	while (ctx->tmp_len + len >= 8)
	{
		ft_memcpy(ctx->tmp + ctx->tmp_len, data, 8 - ctx->tmp_len);
		data += 8 - ctx->tmp_len;
		len -= 8 - ctx->tmp_len;
		ctx->tmp_len = 0;
		tmp = des_operate_block(ctx, *(uint64_t*)ctx->tmp);
		ft_memcpy(ctx->buff + ctx->buff_len, &tmp, 8);
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

int	des_decode_final(t_des_ctx *ctx)
{
	free(ctx->buff);
	return (1);
}
