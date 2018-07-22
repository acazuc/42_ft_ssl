/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_genrsa2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:46:11 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/22 16:39:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	push_data(t_genrsa_data *ctx, uint8_t *data, size_t len)
{
	size_t	tmp;
	int	osef;

	while (ctx->buff_pos + len >= ctx->buff_len)
	{
		tmp = ctx->buff_len - ctx->buff_pos;
		ft_memcpy(ctx->buff + ctx->buff_pos, data, tmp);
		data += tmp;
		len -= tmp;
		osef = write(ctx->fdout, ctx->buff, ctx->buff_len);
		ctx->buff_pos = 0;
	}
	ft_memcpy(ctx->buff + ctx->buff_pos, data, len);
	ctx->buff_pos += len;
	(void)osef;
}

void		cmd_genrsa_b64_callback(t_genrsa_data *ctx, uint8_t *data
		, size_t len)
{
	int		tmp;
	char		nl;

	while (ctx->b64_count + len >= 64)
	{
		tmp = 64 - ctx->b64_count;
		if (tmp > 64)
			tmp = 64;
		push_data(ctx, data, tmp);
		data += tmp;
		len -= tmp;
		ctx->b64_count = 0;
		nl = '\n';
		push_data(ctx, (uint8_t*)&nl, 1);
	}
	ctx->b64_count += len;
	push_data(ctx, data, len);
}

static int	push_b64(t_genrsa_data *data, t_bignum *bignum)
{
	if (!(b64e_update(&data->b64_ctx, (uint8_t*)bignum->data
					, bignum->len * sizeof(*bignum->data))))
	{
		ft_putendl_fd("ft_ssl: base64 encode failed", 2);
		return (0);
	}
	return (1);
}

int		cmd_genrsa_write(t_genrsa_data *data)
{
	uint8_t a;
	
	ft_putendl_fd("-----BEGIN RSA PRIVATE KEY-----", data->fdout);
	a = '0';
	if (!b64e_init(&data->b64_ctx))
		return (0);
	if (!b64e_update(&data->b64_ctx, &a, 1))
		return (0);
	if (!push_b64(data, data->rsa_ctx.n)
			|| !push_b64(data, data->rsa_ctx.e)
			|| !push_b64(data, data->rsa_ctx.d)
			|| !push_b64(data, data->rsa_ctx.p)
			|| !push_b64(data, data->rsa_ctx.q)
			|| !push_b64(data, data->rsa_ctx.dmp)
			|| !push_b64(data, data->rsa_ctx.dmq)
			|| !push_b64(data, data->rsa_ctx.coef))
		return (0);
	if (!b64e_final(&data->b64_ctx))
		return (0);
	a = write(data->fdout, data->buff, data->buff_pos);
	if (data->b64_count)
		ft_putchar_fd('\n', data->fdout);
	ft_putendl_fd("-----END RSA PRIVATE KEY-----", data->fdout);
	return (1);
}
