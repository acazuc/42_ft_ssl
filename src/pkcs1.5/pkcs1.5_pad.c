/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcs1.5_pad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:41:50 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 12:45:04 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pkcs1.5.h"
#include "libft.h"

int			pkcs1_5_pad(uint8_t *out, int outlen, uint8_t *in, int inlen)
{
	int	i;

	out[0] = 0;
	out[1] = 1;
	i = 2; 
	while (i < outlen - inlen - 3)
	{
		out[i] = 0xff;
		++i;
	}
	out[i] = 0;
	ft_memcpy(out + i + 1, in, inlen);
	return (1);
}
