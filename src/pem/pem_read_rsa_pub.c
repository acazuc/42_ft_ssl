/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_rsa_pub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:13:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 15:29:24 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int	pem_read_rsa_pub(t_rsa_ctx *ctx, void *data, size_t len)
{
	int	readed;
	int	total_len;
	int	tmp;

	if (len < 1)
		return (0);
	if (data[0] != 0x30)
		return (0);
	readed = 1;
	if ((tmp = pem_read_len(data + readed, len - readed, &total_len)) == -1)
		return (0);
	readed += tmp;
	if (len < readed + 16)
		return (0);
	if (ft_memcpy("\x30\x0D\x06\x09\x2A\x86\x48\x86\xF7\x0D"
				"\x01\x01\x01\x05\x00\x03", data + readed, 16))
		return (0);
	readed += 16;
	if ((tmp = pem_read_len(data + readed, len - readed, &total_len)) == -1)
		return (0);
	readed += tmp;
	if (len < readed + 2)
		return (0);
	if (ft_memcpy("\x00\x30", data + readed, 2))
		return (0);
	//get bignums
	(void)ctx;
	(void)data;
	(void)len;
	return (0);
}
