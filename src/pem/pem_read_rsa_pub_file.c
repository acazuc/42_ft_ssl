/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_rsa_pub_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:14:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/14 10:07:10 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int	pem_read_rsa_pub_file(t_rsa_ctx *ctx, int fd, char *password)
{
	t_pem_read_ctx	pem_ctx;

	pem_ctx.ciphered = 0;
	pem_ctx.fd = fd;
	pem_ctx.password = password;
	pem_ctx.begin_text = "-----BEGIN PUBLIC KEY-----";
	pem_ctx.end_text = "-----END PUBLIC KEY-----";
	if (!pem_read_file(&pem_ctx))
		return (0);
	if (!pem_read_rsa_pub(ctx, pem_ctx.data, pem_ctx.len))
	{
		free(pem_ctx.data);
		return (0);
	}
	free(pem_ctx.data);
	return (1);
}
