/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_rsa_priv_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:11:27 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 13:49:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int	pem_read_rsa_priv_file(t_rsa_ctx *ctx, int fd, char *password)
{
	t_pem_read_ctx	pem_ctx;

	pem_ctx.ciphered = 1;
	pem_ctx.fd = fd;
	pem_ctx.password = password;
	pem_ctx.begin_text = "-----BEGIN RSA PRIVATE KEY-----";
	pem_ctx.end_text = "-----END RSA PRIVATE KEY-----";
	if (!pem_read_file(&pem_ctx))
		return (0);
	if (!pem_read_rsa_priv(ctx, pem_ctx.data, pem_ctx.len))
		return (0);
	return (1);
}
