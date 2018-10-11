/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:43:50 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:32:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_PROTOTYPES_H
# define FT_SSL_PROTOTYPES_H

void		print_usage();
void		print_usage_commands();
int			command_help(int ac, char **av);
int			command_hash(int ac, char **av, t_hash_data *data);
int			command_md4(int ac, char **av);
int			command_md5(int ac, char **av);
int			command_sha1(int ac, char **av);
int			command_sha224(int ac, char **av);
int			command_sha256(int ac, char **av);
int			command_sha384(int ac, char **av);
int			command_sha512(int ac, char **av);
int			command_crc32(int ac, char **av);
int			command_adler32(int ac, char **av);
int			command_ripemd128(int ac, char **av);
int			command_ripemd160(int ac, char **av);
int			command_ripemd256(int ac, char **av);
int			command_ripemd320(int ac, char **av);
int			command_base64(int ac, char **av);
int			command_des1(int ac, char **av, t_des_data *data);
int			command_des1_ecb(int ac, char **av);
int			command_des1_cbc(int ac, char **av);
int			command_des1_pcbc(int ac, char **av);
int			command_des1_cfb(int ac, char **av);
int			command_des1_ofb(int ac, char **av);
int			command_des1_ctr(int ac, char **av);
int			command_des2(int ac, char **av, t_des_data *data);
int			command_des2_ecb(int ac, char **av);
int			command_des2_cbc(int ac, char **av);
int			command_des2_pcbc(int ac, char **av);
int			command_des2_cfb(int ac, char **av);
int			command_des2_ofb(int ac, char **av);
int			command_des2_ctr(int ac, char **av);
int			command_des3(int ac, char **av, t_des_data *data);
int			command_des3_ecb(int ac, char **av);
int			command_des3_cbc(int ac, char **av);
int			command_des3_pcbc(int ac, char **av);
int			command_des3_cfb(int ac, char **av);
int			command_des3_ofb(int ac, char **av);
int			command_des3_ctr(int ac, char **av);
int			command_aes_128(int ac, char **av, t_aes_data *data);
int			command_aes_128_ecb(int ac, char **av);
int			command_aes_128_cbc(int ac, char **av);
int			command_aes_128_pcbc(int ac, char **av);
int			command_aes_128_cfb(int ac, char **av);
int			command_aes_128_ofb(int ac, char **av);
int			command_aes_128_ctr(int ac, char **av);
int			command_aes_192(int ac, char **av, t_aes_data *data);
int			command_aes_192_ecb(int ac, char **av);
int			command_aes_192_cbc(int ac, char **av);
int			command_aes_192_pcbc(int ac, char **av);
int			command_aes_192_cfb(int ac, char **av);
int			command_aes_192_ofb(int ac, char **av);
int			command_aes_192_ctr(int ac, char **av);
int			command_aes_256(int ac, char **av, t_aes_data *data);
int			command_aes_256_ecb(int ac, char **av);
int			command_aes_256_cbc(int ac, char **av);
int			command_aes_256_pcbc(int ac, char **av);
int			command_aes_256_cfb(int ac, char **av);
int			command_aes_256_ofb(int ac, char **av);
int			command_aes_256_ctr(int ac, char **av);
int			command_camellia_128(int ac, char **av, t_camellia_data *data);
int			command_camellia_128_ecb(int ac, char **av);
int			command_camellia_128_cbc(int ac, char **av);
int			command_camellia_128_pcbc(int ac, char **av);
int			command_camellia_128_cfb(int ac, char **av);
int			command_camellia_128_ofb(int ac, char **av);
int			command_camellia_128_ctr(int ac, char **av);
int			command_camellia_192(int ac, char **av, t_camellia_data *data);
int			command_camellia_192_ecb(int ac, char **av);
int			command_camellia_192_cbc(int ac, char **av);
int			command_camellia_192_pcbc(int ac, char **av);
int			command_camellia_192_cfb(int ac, char **av);
int			command_camellia_192_ofb(int ac, char **av);
int			command_camellia_192_ctr(int ac, char **av);
int			command_camellia_256(int ac, char **av, t_camellia_data *data);
int			command_camellia_256_ecb(int ac, char **av);
int			command_camellia_256_cbc(int ac, char **av);
int			command_camellia_256_pcbc(int ac, char **av);
int			command_camellia_256_cfb(int ac, char **av);
int			command_camellia_256_ofb(int ac, char **av);
int			command_camellia_256_ctr(int ac, char **av);
int			command_chacha20(int ac, char **av);
int			command_rc4(int ac, char **av);
int			command_cipher(int ac, char **av, t_cipher_data *data);
int			cmd_cipher_parse_args(t_cipher_data *data, t_cipher_args *args);
int			cmd_cipher_do_execute(t_cipher_data *data);
int			cmd_cipher_handle_iv(t_cipher_data *data, t_cipher_args *args);
int			cmd_cipher_handle_key(t_cipher_data *data, t_cipher_args *args);
int			cmd_cipher_callback(t_cipher_data *ctx, uint8_t *data, size_t len);
int			cmd_cipher_do_update(t_cipher_data *data);
int			cmd_cipher_init(t_cipher_data *data, t_cipher_args *args, int ac
		, char **av);
void		cmd_cipher_free(t_cipher_data *data);
int			command_bignum(int ac, char **av);
int			command_genrsa(int ac, char **av);
void		cmd_genrsa_b64_callback(t_genrsa_data *ctx, uint8_t *data
		, size_t len);
int			cmd_genrsa_parse_args(t_genrsa_data *data, int ac, char **av);
int			cmd_genrsa_write(t_genrsa_data *data);
int			command_rsa(int ac, char **av);
int			command_rsautl(int ac, char **av);
uint32_t	rotate_left28(uint32_t v, uint32_t c);
uint32_t	rotate_left32(uint32_t v, uint32_t c);
uint64_t	rotate_left64(uint64_t v, uint64_t c);
uint32_t	rotate_right28(uint32_t v, uint32_t c);
uint32_t	rotate_right32(uint32_t v, uint32_t c);
uint64_t	rotate_right64(uint64_t v, uint64_t c);
void		bin2hex(char *dst, const uint8_t *src, size_t len);
int			hex2bin(uint8_t *dst, const char *src, size_t len);
int			random_bytes(uint8_t *dst, int len);
char		*ask_password();
char		*ask_password_confirm();
int			transform_bin(uint8_t *bin, char *str, int max);
void		uint32_swap(uint32_t *a, uint32_t *b);
int			base64_write_init(t_b64_write_ctx *ctx);
int			base64_write_update(t_b64_write_ctx *ctx, uint8_t *data
		, size_t len);
int			base64_write_final(t_b64_write_ctx *ctx);

#endif
