/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 17:42:14 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "base64.h"
# include "libft.h"
# include "rsa.h"
# include "des.h"
# include <stdint.h>
# include <math.h>

typedef struct		s_b64e_data
{
	int		fd;
	int		count;
}			t_b64e_data;

typedef struct		s_b64d_data
{
	int		fd;
}			t_b64d_data;

typedef int (*t_hash_init)(void *ctx);
typedef int (*t_hash_update)(void *ctx, const uint8_t *data, size_t len);
typedef int (*t_hash_final)(uint8_t *md, void *ctx);

typedef struct		s_hash
{
	t_hash_init	init;
	t_hash_update	update;
	t_hash_final	final;
	uint8_t		digest_len;
	uint8_t		block_len;
	char		*name;
}			t_hash;

typedef struct		s_hash_ctx
{
	t_hash		*h;
	void		*ctx;
}			t_hash_ctx;

typedef struct		s_hmac_ctx
{
	t_hash_ctx	h;
	uint8_t		*key;
	uint32_t	key_len;
	uint8_t		*msg;
	uint32_t	msg_len;
}			t_hmac_ctx;

typedef struct		s_pbkdf2_ctx
{
	t_hash_ctx	h;
	uint8_t		*password;
	uint32_t	password_len;
	uint8_t		*salt;
	uint32_t	salt_len;
	uint32_t	iterations;
	uint8_t		*out;
	uint32_t	out_len;
}			t_pbkdf2_ctx;

typedef struct		s_hash_data
{
	t_hash_ctx	h;
	int		reverse;
	int		quiet;
}			t_hash_data;


typedef struct		s_des_data t_des_data;
typedef struct		s_cipher_ctx t_cipher_ctx;

typedef void (*t_cipher_mod)(t_cipher_ctx *ctx, uint8_t *data);
typedef int (*t_cipher_update)(void *userptr, uint8_t *data, size_t len);
typedef int (*t_cipher_cb)(void *userptr, uint8_t *data, size_t len);

struct			s_cipher_ctx
{
	t_cipher_mod	premod;
	t_cipher_mod	postmod;
	t_cipher_update	update;
	t_cipher_cb	callback;
	void		*userptr;
	uint32_t	block_size;
	uint32_t	buff_pos;
	uint8_t		*buff;
	uint8_t		*mod1;
	uint8_t		*mod2;
	uint8_t		*iv;
	int		nopad;
	int		ended;
	int		mode;
	int		mod3;
};

struct			s_des_data
{
	t_cipher_ctx	cipher;
	t_des_ctx	ctx[3];
	char		*buff;
	uint32_t	buff_len;
	uint32_t	buff_pos;
	uint64_t	keys[3];
	int		base64;
	int		fdout;
	int		fdin;
	int		des3;
	union
	{
		t_b64e_ctx	b64e_ctx;
		t_b64d_ctx	b64d_ctx;
	};
	uint64_t	b64_count;
};

typedef struct		s_des_args
{
	char		*password;
	char		*salt;
	char		*key;
	char		*iv;
	char		**av;
	int		ac;
	int		i;
}			t_des_args;

typedef struct		s_b64_write_ctx
{
	int		fdout;
	t_b64e_ctx	b64e_ctx;
	char		*buff;
	uint64_t	count;
	uint64_t	buff_pos;
	uint64_t	buff_len;
}			t_b64_write_ctx;

typedef struct		s_genrsa_data
{
	t_rsa_ctx	rsa_ctx;
	uint64_t	key_len;
	int		fdout;
	t_b64_write_ctx	b64_ctx;
}			t_genrsa_data;

void		print_usage();
void		print_usage_commands();
int		command_hash(int ac, char **av, t_hash_data *data);
int		command_md5(int ac, char **av);
int		command_sha1(int ac, char **av);
int		command_sha224(int ac, char **av);
int		command_sha256(int ac, char **av);
int		command_sha384(int ac, char **av);
int		command_sha512(int ac, char **av);
int		command_base64(int ac, char **av);
int		command_des(int ac, char **av, t_des_data *data);
int		command_des_ecb(int ac, char **av);
int		command_des_cbc(int ac, char **av);
int		command_des_pcbc(int ac, char **av);
int		command_des_cfb(int ac, char **av);
int		command_des_ofb(int ac, char **av);
int		command_des2(int ac, char **av, t_des_data *data);
int		command_des2_ecb(int ac, char **av);
int		command_des2_cbc(int ac, char **av);
int		command_des2_pcbc(int ac, char **av);
int		command_des2_cfb(int ac, char **av);
int		command_des2_ofb(int ac, char **av);
int		command_des3(int ac, char **av, t_des_data *data);
int		command_des3_ecb(int ac, char **av);
int		command_des3_cbc(int ac, char **av);
int		command_des3_pcbc(int ac, char **av);
int		command_des3_cfb(int ac, char **av);
int		command_des3_ofb(int ac, char **av);
int		cmd_des_parse_args(t_des_data *data, t_des_args *args);
int		cmd_des_do_execute(t_des_data *data);
int		cmd_des_handle_iv(t_des_data *data, t_des_args *args);
int		cmd_des_handle_key(t_des_data *data, t_des_args *args);
int		cmd_des_callback(t_des_data *ctx, uint8_t *data, size_t len);
int		cmd_des_do_update(t_des_data *data);
int		cmd_des_init(t_des_data *data, t_des_args *args, int ac, char **av);
void		cmd_des_free(t_des_data *data);
int		command_bignum(int ac, char **av);
int		command_genrsa(int ac, char **av);
void		cmd_genrsa_b64_callback(t_genrsa_data *ctx, uint8_t *data, size_t len);
int		cmd_genrsa_write(t_genrsa_data *data);
void		cipher_ecb_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_ecb_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cbc_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cbc_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_pcbc_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_pcbc_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cfb_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_cfb_postmod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_ofb_premod(t_cipher_ctx *ctx, uint8_t *data);
void		cipher_ofb_postmod(t_cipher_ctx *ctx, uint8_t *data);
int		cipher_init(t_cipher_ctx *ctx, uint32_t block_size);
int		cipher_update(t_cipher_ctx *ctx, uint8_t *data, size_t len);
int		cipher_final(t_cipher_ctx *ctx);
void		cipher_free(t_cipher_ctx *ctx);
uint32_t	rotate_left28(uint32_t v, uint32_t c);
uint32_t	rotate_left32(uint32_t v, uint32_t c);
uint64_t	rotate_left64(uint64_t v, uint64_t c);
uint32_t	rotate_right28(uint32_t v, uint32_t c);
uint32_t	rotate_right32(uint32_t v, uint32_t c);
uint64_t	rotate_right64(uint64_t v, uint64_t c);
void		bin2hex(char *dst, const uint8_t *src, size_t len);
int		hex2bin(uint8_t *dst, const char *src, size_t len);
int		random_bytes(uint8_t *dst, int len);
uint8_t		*hmac(t_hmac_ctx *ctx);
int		pbkdf2(t_pbkdf2_ctx *ctx);
int		base64_write_init(t_b64_write_ctx *ctx);
int		base64_write_update(t_b64_write_ctx *ctx, uint8_t *data, size_t len);
int		base64_write_final(t_b64_write_ctx *ctx);

#endif
