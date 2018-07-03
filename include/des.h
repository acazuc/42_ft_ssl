/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:26:57 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/03 21:49:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

typedef struct s_des_ctx	t_des_ctx;

typedef int (*t_des_callback)(uint8_t *data, size_t len, void *userptr);
typedef void (*t_des_premod)(t_des_ctx *ctx, uint64_t *data);
typedef void (*t_des_postmod)(t_des_ctx *ctx, uint64_t *data);

struct		s_des_ctx
{
	t_des_premod	pre_mod;
	t_des_postmod	post_mod;
	t_des_callback	callback;
	void		*userptr;
	uint8_t		*buff;
	uint32_t	buff_len;
	uint64_t	keys[16];
	uint64_t	prev_val;
	uint8_t		tmp[8];
	uint8_t		tmp_len;
	uint64_t	iv;
	uint64_t	tmp1;
	uint64_t	tmp2;
	int		mode;
	int		nopad;
};

void	des_generate_keys(t_des_ctx *ctx, uint64_t key);
void	des_operate_block(t_des_ctx *ctx, uint64_t *block);

int	des_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_encrypt_update(t_des_ctx *ctx, const uint8_t *data, size_t len);
int	des_encrypt_final(t_des_ctx *ctx);

int	des_ecb_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_cbc_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_pcbc_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_cfb_encrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_ofb_encrypt_init(t_des_ctx *ctx, uint64_t key);

int	des_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_decrypt_update(t_des_ctx *ctx, const uint8_t *data, size_t len);
int	des_decrypt_final(t_des_ctx *ctx);

int	des_ecb_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_cbc_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_pcbc_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_cfb_decrypt_init(t_des_ctx *ctx, uint64_t key);
int	des_ofb_decrypt_init(t_des_ctx *ctx, uint64_t key);

# define DES_BUFF_LEN 1024

#endif
