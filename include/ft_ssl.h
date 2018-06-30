/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 15:00:34 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
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

typedef struct	s_hash
{
	t_hash_init	*init;
	t_hash_update	*update;
	t_hash_final	*final;
	uint8_t		digest_len;
	uint8_t		block_len;
	char		*name;
}		t_hash;

typedef struct	s_hash_ctx
{
	t_hash		*h;
	void		*ctx;
}		t_hash_ctx;

typedef struct	s_hmac_ctx
{
	t_hash_ctx	h;
	uint8_t		*key;
	uint32_t	key_len;
	uint8_t		*msg;
	uint32_t	msg_len;
}		t_hmac_ctx;

typedef struct	s_pbkdf2_ctx
{
	t_hash_ctx	h;
	uint8_t		*password;
	uint32_t	password_len;
	uint8_t		*salt;
	uint32_t	salt_len;
	uint32_t	iterations;
	uint8_t		*out;
	uint32_t	out_len;
}		t_pbkdf2_ctx;

typedef struct	s_hash_data
{
	t_hash_ctx	h;
	int		reverse;
	int		quiet;
}		t_hash_data;

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
int		command_des(int ac, char **av);
int		command_des_ecb(int ac, char **av);
int		command_des_cbc(int ac, char **av);
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
