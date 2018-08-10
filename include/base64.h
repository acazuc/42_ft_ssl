/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 23:25:36 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:36:33 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include <stdint.h>
# include <stddef.h>

typedef void (*t_b64_callback)(void *userptr, uint8_t *data, size_t len);

typedef struct		s_b64e_ctx
{
	t_b64_callback	callback;
	void		*userptr;
	uint8_t		*buff;
	uint32_t	buff_len;
	uint8_t		tmp[3];
	uint8_t		tmp_len;
}			t_b64e_ctx;

typedef struct		s_b64d_ctx
{
	t_b64_callback	callback;
	void		*userptr;
	uint8_t		*buff;
	uint32_t	buff_len;
	uint8_t		tmp[4];
	uint8_t		tmp_len;
}			t_b64d_ctx;

int	b64e_init(t_b64e_ctx *ctx);
int	b64e_update(t_b64e_ctx *ctx, const uint8_t *data, size_t len);
int	b64e_final(t_b64e_ctx *ctx);

int	b64d_init(t_b64d_ctx *ctx);
int	b64d_update(t_b64d_ctx *ctx, const uint8_t *data, size_t len);
int	b64d_final(t_b64d_ctx *ctx);

# define BASE64_BUFF_LEN 1024

#endif
