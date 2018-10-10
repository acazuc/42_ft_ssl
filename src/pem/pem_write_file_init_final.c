/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_file_init_final.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:26:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 13:26:43 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

int	pem_write_init(t_pem_write_ctx *ctx)
{
	if (!base64_write_init(&ctx->b64_ctx))
	{
		ft_putendl_fd("ft_ssl: failed to init b64 ctx", 2);
		return (0);
	}
	if (ctx->ciphered && !ctx->cipher)
	{
		ft_putendl_fd("ft_ssl: invalid cipher", 2);
		return (0);
	}
	return (1);
}

int	pem_write_final(t_pem_write_ctx *ctx)
{
	base64_write_final(&ctx->b64_ctx);
	ft_putendl_fd(ctx->end_text, ctx->b64_ctx.fdout);
	return (1);
}
