/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecu8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 15:35:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 16:33:47 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "vecu8.h"

void	vecu8_init(t_vecu8 *vec)
{
	vec->data = NULL;
	vec->size = 0;
}

int	vecu8_pushu8(t_vecu8 *vec, uint8_t u8)
{
	return (vecu8_push(vec, &u8, 1));
}

int	vecu8_push(t_vecu8 *vec, uint8_t *data, size_t len)
{
	uint8_t	*tmp;

	if (!len)
		return (1);
	if (!(tmp = malloc(vec->size + len)))
		return (0);
	ft_memcpy(tmp, vec->data, vec->size);
	free(vec->data);
	vec->data = tmp;
	ft_memcpy(tmp + vec->size, data, len);
	vec->size += len;
	return (1);
}

void	vecu8_free(t_vecu8 *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->size = 0;
}
