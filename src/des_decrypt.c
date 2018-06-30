/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 22:45:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 19:17:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

int	des_decrypt_init(t_des_ctx *ctx, uint64_t key)
{
	des_generate_keys(ctx, key);
	ctx->mode = 1;
	if (!(ctx->buff = malloc(DES_BUFF_LEN * sizeof(*ctx->buff))))
		return (0);
	return (1);
}

int	des_decrypt_update(t_des_ctx *ctx, const uint8_t *data, size_t len)
{
	uint64_t	tmp;

	ctx->buff_len = 0;
	while (ctx->tmp_len + len >= 8)
	{
		ft_memcpy(ctx->tmp + ctx->tmp_len, data, 8 - ctx->tmp_len);
		data += 8 - ctx->tmp_len;
		len -= 8 - ctx->tmp_len;
		ctx->tmp_len = 0;
		tmp = *(uint64_t*)ctx->tmp;
		ctx->pre_mod(ctx, &tmp);
		tmp = des_operate_block(ctx, tmp);
		ctx->post_mod(ctx, &tmp);
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

int	des_decrypt_final(t_des_ctx *ctx)
{
	free(ctx->buff);
	return (1);
}
