/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:45:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:32:54 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_STRUCTS_H
# define FT_SSL_STRUCTS_H

typedef struct		s_program
{
	char			*name;
	int				(*fn)(int ac, char **av);
}					t_program;

typedef struct		s_b64e_data
{
	int				fd;
	int				count;
}					t_b64e_data;

typedef struct		s_b64d_data
{
	int				fd;
}					t_b64d_data;

typedef struct		s_b64_write_ctx
{
	t_b64e_ctx		b64e_ctx;
	int				fdout;
	char			*buff;
	uint64_t		count;
	uint64_t		buff_pos;
	uint64_t		buff_len;
}					t_b64_write_ctx;

typedef struct		s_hash_data
{
	t_hash_ctx		h;
	int				reverse;
	int				written;
	int				quiet;
}					t_hash_data;

typedef struct		s_cipher_data
{
	t_cipher_ctx	cipher;
	char			*buff;
	uint32_t		buff_len;
	uint32_t		buff_pos;
	uint8_t			*key;
	uint8_t			*iv;
	int				base64;
	int				fdout;
	int				fdin;
	t_b64_write_ctx	b64e_ctx;
	t_b64d_ctx		b64d_ctx;
}					t_cipher_data;

typedef struct		s_cipher_args
{
	char			*password;
	char			*salt;
	char			*key;
	char			*iv;
	char			**av;
	int				ac;
	int				i;
}					t_cipher_args;

typedef struct		s_des_data
{
	t_cipher_data	cipher;
	uint8_t			key[24];
	uint8_t			iv[8];
}					t_des_data;

typedef struct		s_aes_data
{
	t_cipher_data	cipher;
	uint8_t			key[32];
	uint8_t			iv[16];
}					t_aes_data;

typedef struct		s_camellia_data
{
	t_cipher_data	cipher;
	uint8_t			key[32];
	uint8_t			iv[16];
}					t_camellia_data;

typedef struct		s_chacha20_data
{
	t_cipher_data	cipher;
	uint8_t			key[32];
	uint8_t			iv[64];
}					t_chacha20_data;

typedef struct		s_rc4_data
{
	t_cipher_data	cipher;
	uint8_t			key[16];
	uint8_t			iv[1];
}					t_rc4_data;

typedef struct		s_genrsa_data
{
	t_rsa_ctx		rsa_ctx;
	uint64_t		key_len;
	int				fdout;
	char			*crypt_method;
	char			*passout;
	uint32_t		exp;
}					t_genrsa_data;

typedef struct		s_openssl_pbkdf_ctx
{
	t_hash			*hash;
	uint8_t			*key;
	size_t			key_len;
	uint8_t			*pw;
	size_t			pw_len;
	uint8_t			*iv;
	size_t			iv_len;
}					t_openssl_pbkdf_ctx;

#endif
