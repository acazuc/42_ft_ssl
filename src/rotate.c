/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:18:18 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 10:45:23 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rotate_left(uint32_t v, uint32_t c)
{
	return ((v << c) | (v >> (32 - c)));
}

uint64_t	rotate_left64(uint64_t v, uint64_t c)
{
	return ((v << c) | (v >> (64 - c)));
}

uint32_t	rotate_right(uint32_t v, uint32_t c)
{
	return ((v >> c) | (v << (32 - c)));
}

uint64_t	rotate_right64(uint64_t v, uint64_t c)
{
	return ((v >> c) | (v << (64 - c)));
}
