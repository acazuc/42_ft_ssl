/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:26:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 22:32:51 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

typedef void (*t_des_callback)(uint8_t *data, size_t len, void *userptr);

typedef struct		s_des_ctx
{
	t_des_callback	callback;
	void		*userptr;
	uint8_t		*buff;
	uint32_t	buff_len;
	uint64_t	keys[16];
	uint64_t	prev_val;
	uint8_t		tmp[8];
	uint8_t		tmp_len;
	int		block_mode;
	int		mode;
}			t_des_ctx;

void		des_generate_keys(t_des_ctx *ctx, uint64_t key);
uint64_t	des_operate_block(t_des_ctx *ctx, uint64_t block);
int		des_init(t_des_ctx *ctx, uint64_t key, t_des_callback callback, void *userptr);
int		des_update(t_des_ctx *ctx, const uint8_t *data, size_t len);
int		des_final(t_des_ctx *ctx);

# define DES_BUFF_LEN 1024

#endif
