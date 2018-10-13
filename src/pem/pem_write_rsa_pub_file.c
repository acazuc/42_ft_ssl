/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_write_rsa_pub_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:14:30 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 12:22:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int			pem_write_rsa_pub_file(t_rsa_ctx *ctx, int fd, char *cipher_name
		, char *password)
{
	t_pem_write_ctx	pem_ctx;

	(void)cipher_name;
	(void)password;
	pem_ctx.b64_ctx.fdout = fd;
	pem_ctx.ciphered = 0;
	pem_ctx.cipher = NULL;
	pem_ctx.password = NULL;
	pem_ctx.begin_text = "-----BEGIN PUBLIC KEY-----";
	pem_ctx.end_text = "-----END PUBLIC KEY-----";
	if ((pem_ctx.len = pem_write_rsa_pub(&pem_ctx.data, ctx)) == -1)
	{
		ft_putendl_fd("ft_ssl: failed to generate pem file", 2);
		return (0);
	}
	if (!pem_write_init(&pem_ctx) || !pem_write_write(&pem_ctx)
			|| !pem_write_final(&pem_ctx))
	{
		free(pem_ctx.data);
		return (0);
	}
	free(pem_ctx.data);
	return (1);
}
