/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcs1.5_unpad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:44:38 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 12:46:37 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pkcs1.5.h"
#include "libft.h"

int	pkcs1_5_unpad(uint8_t *out, int *outlen, uint8_t *in, int inlen)
{
	int	i;

	if (!inlen)
		return (0);
	if (!in[0])
	{
		in++;
		inlen--;
	}
	if (!inlen || in[0] != 1)
		return (0);
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
