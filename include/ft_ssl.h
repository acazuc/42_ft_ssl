/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 15:26:15 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "des.h"
# include <stdint.h>
# include <math.h>

typedef struct	s_b64e_data
{
	int	fd;
	int	count;
}		t_b64e_data;

typedef struct	s_b64d_data
{
	int	fd;
}		t_b64d_data;

typedef int t_hash_init(void *ctx);
typedef int t_hash_update(void *ctx, const uint8_t *data, size_t len);
typedef int t_hash_final(uint8_t *md, void *ctx);

typedef struct		s_hash
{
	t_hash_init	*init;
	t_hash_update	*update;
	t_hash_final	*final;
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

typedef int t_des_init(void *ctx, int64_t key);

typedef struct		s_des_data
{
	t_des_init	*encrypt_init;
	t_des_init	*decrypt_init;
	t_des_ctx	ctx1;
	t_des_ctx	ctx2;
	t_des_ctx	ctx3;
	uint64_t	key1;
	uint64_t	key2;
	uint64_t	key3;
	int		base64;
	int		fdout;
	int		fdin;
	int		mode;
	int		des3;
	void		*b64_ctx;
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
int		cmd_des_handle_iv(t_des_ctx *ctx, char *iv);
int		cmd_des_handle_key(t_des_data *data, t_des_args *args);
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

#endif
