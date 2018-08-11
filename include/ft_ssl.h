/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/11 19:05:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "base64.h"
# include "cipher.h"
# include "libft.h"
# include "hash.h"
# include "rsa.h"
# include "des.h"
# include "aes.h"
# include <stdint.h>
# include <math.h>

typedef struct		s_program
{
	char		*name;
	int		(*fn)(int ac, char **av);
}			t_program;

typedef struct		s_b64e_data
{
	int		fd;
	int		count;
}			t_b64e_data;

typedef struct		s_b64d_data
{
	int		fd;
}			t_b64d_data;

typedef struct		s_b64_write_ctx
{
	t_b64e_ctx	b64e_ctx;
	int		fdout;
	char		*buff;
	uint64_t	count;
	uint64_t	buff_pos;
	uint64_t	buff_len;
}			t_b64_write_ctx;

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
	int		written;
	int		quiet;
}			t_hash_data;

typedef struct		s_des_data
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
	t_b64_write_ctx	b64e_ctx;
	t_b64d_ctx	b64d_ctx;
}			t_des_data;

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

typedef struct		s_aes_data
{
	t_cipher_ctx	cipher;
	t_aes_ctx	ctx;
	char		*buff;
	uint32_t	buff_len;
	uint32_t	buff_pos;
	int		key_size;
	uint8_t		key[32];
	int		base64;
	int		fdout;
	int		fdin;
	t_b64_write_ctx	b64e_ctx;
	t_b64d_ctx	b64d_ctx;
}			t_aes_data;

typedef struct		s_aes_args
{
	char		*password;
	char		*salt;
	char		*key;
	char		*iv;
	char		**av;
	int		ac;
	int		i;
}			t_aes_args;

typedef struct		s_genrsa_data
{
	t_rsa_ctx	rsa_ctx;
	uint64_t	key_len;
	int		fdout;
	uint32_t	crypt_method;
	uint32_t	exp;
	t_b64_write_ctx	b64_ctx;
}			t_genrsa_data;

void		print_usage();
void		print_usage_commands();
int		command_help(int ac, char **av);
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
int		command_aes_128(int ac, char **av, t_aes_data *data);
int		command_aes_128_ecb(int ac, char **av);
int		command_aes_128_cbc(int ac, char **av);
int		command_aes_128_pcbc(int ac, char **av);
int		command_aes_128_cfb(int ac, char **av);
int		command_aes_128_ofb(int ac, char **av);
int		command_aes_192(int ac, char **av, t_aes_data *data);
int		command_aes_192_ecb(int ac, char **av);
int		command_aes_192_cbc(int ac, char **av);
int		command_aes_192_pcbc(int ac, char **av);
int		command_aes_192_cfb(int ac, char **av);
int		command_aes_192_ofb(int ac, char **av);
int		command_aes_256(int ac, char **av, t_aes_data *data);
int		command_aes_256_ecb(int ac, char **av);
int		command_aes_256_cbc(int ac, char **av);
int		command_aes_256_pcbc(int ac, char **av);
int		command_aes_256_cfb(int ac, char **av);
int		command_aes_256_ofb(int ac, char **av);
int		cmd_aes_parse_args(t_aes_data *data, t_aes_args *args);
int		cmd_aes_do_execute(t_aes_data *data);
int		cmd_aes_handle_iv(t_aes_data *data, t_aes_args *args);
int		cmd_aes_handle_key(t_aes_data *data, t_aes_args *args);
int		cmd_aes_callback(t_aes_data *ctx, uint8_t *data, size_t len);
int		cmd_aes_do_update(t_aes_data *data);
int		cmd_aes_init(t_aes_data *data, t_aes_args *args, int ac, char **av);
void		cmd_aes_free(t_aes_data *data);
int		command_bignum(int ac, char **av);
int		command_genrsa(int ac, char **av);
void		cmd_genrsa_b64_callback(t_genrsa_data *ctx, uint8_t *data, size_t len);
int		cmd_genrsa_write(t_genrsa_data *data);
int		command_rsa(int ac, char **av);
int		command_rsautl(int ac, char **av);
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
