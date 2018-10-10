/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:46:47 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/10 12:07:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PEM_H
# define PEM_H

# include "cipher/cipher.h"
# include "bignum.h"
# include "ft_ssl.h"
# include "vecu8.h"
# include <stdint.h>

typedef struct s_rsa_ctx		t_rsa_ctx;
typedef struct s_b64_write_ctx	t_b64_write_ctx;

typedef struct		s_pem_write_ctx
{
	t_b64_write_ctx	b64_ctx;
	t_cipher		*cipher;
	int				ciphered;
	char			*data;
	int32_t			len;
	char			*begin_text;
	char			*end_text;
}					t_pem_write_ctx;

uint32_t			pem_len_len(uint32_t len);
uint32_t			pem_write_len(uint8_t *data, uint32_t len);
int32_t				pem_read_len(uint8_t *data, uint32_t len
		, uint32_t *result);
uint32_t			pem_bignum_len(t_bignum *bignum);
int					pem_get_key(t_cipher_ctx *ctx, uint8_t *key
		, uint8_t *salt_iv, char *password);
int					pem_print_ciphered(t_pem_write_ctx *ctx);
int					pem_write_init(t_pem_write_ctx *ctx);
int					pem_write_write(t_pem_write_ctx *ctx);
int					pem_write_final(t_pem_write_ctx *ctx);
int					pem_write_bignum(t_vecu8 *data, t_bignum *bignum);
int					pem_write_rsa_priv(char **dst, t_rsa_ctx *ctx);
int					pem_write_rsa_priv_file(t_rsa_ctx *ctx, int fd
		, char *cipher_name);
int					pem_write_rsa_pub(char **dst, t_rsa_ctx *ctx);
int					pem_write_rsa_pub_file(t_rsa_ctx *ctx, int fd
		, char *cipher_name);

#endif
