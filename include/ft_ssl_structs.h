/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:45:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 11:58:15 by acazuc           ###   ########.fr       */
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
	char			*cipher_name;
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

# define RSA_FORMAT_PEM 1

typedef struct		s_rsa_data
{
	int				inform;
	int				outform;
	char			*passin;
	char			*passout;
	int				fdin;
	int				fdout;
	int				pubin;
	int				pubout;
	int				print_text;
	int				print_modulus;
	int				noout;
	int				check;
	char			*cipher_name;
}					t_rsa_data;

# define RSAUTL_MODE_ENCRYPT	0
# define RSAUTL_MODE_DECRYPT	1
# define RSAUTL_MODE_SIGN		2
# define RSAUTL_MODE_VERIFY		3

typedef struct		s_rsautl_data
{
	int				fdin;
	int				fdout;
	int				keyfd;
	int				pubin;
	int				mode;
	int				hexdump;
	char			*passin;
}					t_rsautl_data;

#endif
