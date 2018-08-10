/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:26:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:34:28 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include <stdint.h>

typedef struct s_des_ctx	t_des_ctx;

struct		s_des_ctx
{
	uint64_t	keys[16];
};

void	des_generate_keys(t_des_ctx *ctx, uint64_t key);
void	des_operate_block(t_des_ctx *ctx, uint64_t *block, int mode);

int	des_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_encrypt_update(t_des_ctx *ctx, uint64_t *data, size_t len);
int	des_encrypt_final(t_des_ctx *ctx);

int	des_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_decrypt_update(t_des_ctx *ctx, uint64_t *data, size_t len);
int	des_decrypt_final(t_des_ctx *ctx);

# define DES_BUFF_LEN 1024

#endif
