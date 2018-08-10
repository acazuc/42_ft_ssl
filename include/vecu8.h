/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecu8.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:07:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:39:40 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECU8_H
# define VECU8_H

# include <stdint.h>
# include <stddef.h>

typedef struct		s_vecu8
{
	uint8_t		*data;
	size_t		size;
}			t_vecu8;

void		vecu8_init(t_vecu8 *vec);
int		vecu8_get(t_vecu8 *vec, void *data, uint32_t len);
int		vecu8_push(t_vecu8 *vec, uint8_t *data, size_t len);
int		vecu8_pushu8(t_vecu8 *vec, uint8_t u8);
void		vecu8_free(t_vecu8 *vec);

#endif
