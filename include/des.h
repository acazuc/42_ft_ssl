/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:26:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 19:54:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include <stddef.h>
# include <stdint.h>

typedef struct		s_des_ctx
{
	uint64_t	keys[16];
}			t_des_ctx;

typedef struct		s_des1_ctx
{
	t_des_ctx	ctx;
}			t_des1_ctx;

typedef struct		s_des2_ctx
{
	t_des_ctx	ctx1;
	t_des_ctx	ctx2;
}			t_des2_ctx;

typedef struct		s_des3_ctx
{
	t_des_ctx	ctx1;
	t_des_ctx	ctx2;
	t_des_ctx	ctx3;
}			t_des3_ctx;

void	des_generate_keys(t_des_ctx *ctx, uint64_t key);
void	des_operate_block(t_des_ctx *ctx, uint64_t *block, int mode);

int	des_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_encrypt_update(t_des_ctx *ctx, uint8_t *data, size_t len);
int	des_encrypt_final(t_des_ctx *ctx);

int	des_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_decrypt_update(t_des_ctx *ctx, uint8_t *data, size_t len);
int	des_decrypt_final(t_des_ctx *ctx);

int	des_ext_encrypt_update(t_des_ctx *ctx, uint8_t *data, size_t len);
int	des_ext_decrypt_update(t_des_ctx *ctx, uint8_t *data, size_t len);
int	des3_ext_encrypt_update(t_des_ctx *ctx, uint8_t *data, size_t len);
int	des3_ext_decrypt_update(t_des_ctx *ctx, uint8_t *data, size_t len);

# define DES_BUFF_LEN 1024

#endif
