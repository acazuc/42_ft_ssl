/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcs1.5_pad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:41:50 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 11:58:36 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pkcs1.5.h"
#include "libft.h"
#include "hash/sha1.h"
#include "ft_ssl.h"

int			pkcs1_5_pad_1(uint8_t *out, int outlen, uint8_t *in, int inlen)
{
	int	i;

	out[0] = 0;
	out[1] = 1;
	i = 2;
	ft_memset(out + 2, 0xff, outlen - inlen - 3);
	i += outlen - inlen - 3;
	out[i] = 0;
	ft_memcpy(out + i + 1, in, inlen);
	return (1);
}

static int	do_fill(uint8_t *out, int len)
{
	t_sha1_ctx	ctx;
	uint8_t		digest[20];
	uint8_t		random[10];
	int			i;

	if (!random_bytes(random, 10))
		return (-1);
	if (!sha1_init(&ctx))
		return (-1);
	if (!sha1_update(&ctx, random, 10))
		return (-1);
	if (!sha1_final(digest, &ctx))
		return (-1);
	i = 0;
	while (i < len && i < 20)
	{
		if (!digest[i])
			return (i);
		out[i] = digest[i];
		++i;
	}
	return (i);
}

int			pkcs1_5_pad_2(uint8_t *out, int outlen, uint8_t *in, int inlen)
{
	int	tmp;
	int	i;

	out[0] = 0;
	out[1] = 2;
	i = 2;
	while (i < outlen - inlen - 1)
	{
		if ((tmp = do_fill(out + i, outlen - inlen - 1 - i)) == -1)
			return (0);
		i += tmp;
	}
	out[i] = 0;
	ft_memcpy(out + i + 1, in, inlen);
	return (1);
}
