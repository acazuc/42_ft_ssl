/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes_shiftrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 22:10:58 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 15:19:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aes.h"

void	aes_shiftrows(uint8_t *block)
{
	uint8_t	tmp;

	tmp = block[1];
	block[1] = block[5];
	block[5] = block[9];
	block[9] = block[13];
	block[13] = tmp;
	tmp = block[3];
	block[3] = block[15];
	block[15] = block[11];
	block[11] = block[7];
	block[7] = tmp;
	tmp = block[10];
	block[10] = block[2];
	block[2] = tmp;
	tmp = block[14];
	block[14] = block[6];
	block[6] = tmp;
}

void	aes_invshiftrows(uint8_t *block)
{
	uint8_t	tmp;

	tmp = block[13];
	block[13] = block[9];
	block[9] = block[5];
	block[5] = block[1];
	block[1] = tmp;
	tmp = block[7];
	block[7] = block[11];
	block[11] = block[15];
	block[15] = block[3];
	block[3] = tmp;
	tmp = block[2];
	block[2] = block[10];
	block[10] = tmp;
	tmp = block[6];
	block[6] = block[14];
	block[14] = tmp;
}
