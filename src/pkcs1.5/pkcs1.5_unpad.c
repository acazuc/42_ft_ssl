/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcs1.5_unpad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:44:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 11:59:02 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pkcs1.5.h"
#include "libft.h"

static int	unpad_1(uint8_t *out, int *outlen, uint8_t *in, int inlen)
{
	int	i;

	i = 1;
	while (i < inlen && in[i] == 0xff)
		++i;
	if (i == inlen || in[i])
		return (0);
	++i;
	ft_memcpy(out, in + i, inlen - i);
	*outlen = inlen - i;
	return (1);
}

static int	unpad_2(uint8_t *out, int *outlen, uint8_t *in, int inlen)
{
	int	i;

	i = 1;
	while (i < inlen && in[i])
		++i;
	if (i == inlen)
		return (0);
	++i;
	ft_memcpy(out, in + i, inlen - i);
	*outlen = inlen - i;
	return (1);
}

int			pkcs1_5_unpad(uint8_t *out, int *outlen, uint8_t *in, int inlen)
{
	if (!inlen)
		return (0);
	if (!in[0])
	{
		in++;
		inlen--;
	}
	if (!inlen)
		return (0);
	if (in[0] == 1)
		return (unpad_1(out, outlen, in, inlen));
	else if (in[0] == 2)
		return (unpad_2(out, outlen, in, inlen));
	return (0);
}
