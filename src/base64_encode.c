/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:19:31 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 09:29:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"

int	b64e_init(t_b64e_ctx *ctx, t_b64e_callback callback, void *userptr)
{
	ctx->callback = callback;
	ctx->userptr = userptr;
	if (!(ctx->buff = malloc(1024 * sizeof(*ctx->buff))))
		return (0);
	return (1);
}

int	b64e_update(t_b64e_ctx *ctx, const uint8_t *data, size_t len)
{
	//ctx->callback(ctx->buff, len, ctx->userptr);
	(void)ctx;
	(void)data;
	(void)len;
	return (1);
}

int	b64e_finish(t_b64e_ctx *ctx)
{
	free(ctx->buff);
	return (1);
}
