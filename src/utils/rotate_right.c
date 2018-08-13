/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:53:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 23:06:53 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rotate_right28(uint32_t v, uint32_t c)
{
	return ((v >> c) | (v << (28 - c)));
}

uint32_t	rotate_right32(uint32_t v, uint32_t c)
{
	return ((v >> c) | (v << (32 - c)));
}

uint64_t	rotate_right64(uint64_t v, uint64_t c)
{
	return ((v >> c) | (v << (64 - c)));
}
