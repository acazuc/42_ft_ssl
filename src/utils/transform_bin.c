/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 13:47:00 by acazuc            #+#    #+#             */
/*   Updated: 2019/05/23 17:43:18 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	transform_bin(uint8_t *bin, char *str, int max)
{
	int	len;

	ft_memset(bin, 0, max);
	len = ft_strlen(str);
	if (len > max * 2)
		len = max * 2;
	if (!hex2bin(bin, str, len))
		return (0);
	return (1);
}
