# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 06:50:12 by acazuc            #+#    #+#              #
#    Updated: 2018/08/14 20:35:42 by acazuc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc

LDFLAGS = -flto=4 -fwhole-program

CFLAGS = -Wall -Wextra -Werror -Ofast -march=native -g -rdynamic
#CFLAGS+= -fsanitize=address
#CFLAGS+= -flto

INCLUDES = -I include/ -I libft/include

SRCS_PATH = src/

SRCS_NAME = main.c \
	    print_usage.c \
	    base64_write.c \
	    utils/rotate_left.c \
	    utils/rotate_right.c \
	    utils/hex_bin.c \
	    utils/random_bytes.c \
	    utils/vecu8.c \
	    utils/ask_password.c \
	    utils/transform_bin.c \
	    hmac/hmac.c \
	    pbkdf2/pbkdf2.c \
	    command/command_help.c \
	    command/command_hash.c \
	    command/command_md4.c \
	    command/command_md5.c \
	    command/command_sha1.c \
	    command/command_sha224.c \
	    command/command_sha256.c \
	    command/command_sha384.c \
	    command/command_sha512.c \
	    command/command_crc32.c \
	    command/command_adler32.c \
	    command/command_base64.c \
	    command/command_des1.c \
	    command/command_des1_2.c \
	    command/command_des2.c \
	    command/command_des2_2.c \
	    command/command_des3.c \
	    command/command_des3_2.c \
	    command/command_aes_128.c \
	    command/command_aes_128_2.c \
	    command/command_aes_192.c \
	    command/command_aes_192_2.c \
	    command/command_aes_256.c \
	    command/command_aes_256_2.c \
	    command/command_camellia_128.c \
	    command/command_camellia_128_2.c \
	    command/command_camellia_192.c \
	    command/command_camellia_192_2.c \
	    command/command_camellia_256.c \
	    command/command_camellia_256_2.c \
	    command/command_chacha20.c \
	    command/command_rc4.c \
	    command/command_cipher.c \
	    command/command_cipher_common1.c \
	    command/command_cipher_execute.c \
	    command/command_cipher_args.c \
	    command/command_cipher_callback.c \
	    command/command_bignum.c \
	    command/command_genrsa.c \
	    command/command_rsa.c \
	    command/command_rsautl.c \
	    hash/md4.c \
	    hash/md5.c \
	    hash/sha1.c \
	    hash/sha224.c \
	    hash/sha256.c \
	    hash/sha384.c \
	    hash/sha512.c \
	    hash/crc32.c \
	    hash/adler32.c \
	    base64/base64_encode.c \
	    base64/base64_decode.c \
	    des/des.c \
	    des/des1.c \
	    des/des2.c \
	    des/des3.c \
	    aes/aes.c \
	    aes/aes128.c \
	    aes/aes192.c \
	    aes/aes256.c \
	    aes/aes_mixcolumns.c \
	    aes/aes_shiftrows.c \
	    aes/aes_subbytes.c \
	    aes/aes_keyschedule.c \
	    aes/aes_rcon.c \
	    chacha20/chacha20.c \
	    chacha20/chacha20_ext.c \
	    rc4/rc4.c \
	    rc4/rc4_ext.c \
	    camellia/camellia_keyschedule.c \
	    camellia/camellia_f.c \
	    camellia/camellia_fl.c \
	    camellia/camellia_encrypt.c \
	    camellia/camellia_decrypt.c \
	    camellia/camellia128.c \
	    camellia/camellia192.c \
	    camellia/camellia256.c \
	    cipher/cipher.c \
	    cipher/cipher_get.c \
	    cipher/cipher_mod_ecb.c \
	    cipher/cipher_mod_cbc.c \
	    cipher/cipher_mod_pcbc.c \
	    cipher/cipher_mod_cfb.c \
	    cipher/cipher_mod_ofb.c \
	    cipher/cipher_mod_ctr64.c \
	    cipher/cipher_mod_ctr128.c \
	    rsa/rsa_genkey.c \
	    rsa/rsa_genkey_pq.c \
	    rsa/rsa_genkey_phi.c \
	    rsa/rsa_genkey_crt.c \
	    rsa/rsa.c \
	    rsa/rsa_free.c \
	    bignum/bignum_print.c \
	    bignum/bignum_printhex.c \
	    bignum/bignum_dec2bignum.c \
	    bignum/bignum_hex2bignum.c \
	    bignum/bignum_npot.c \
	    bignum/bignum_new.c \
	    bignum/bignum_free.c \
	    bignum/bignum_init.c \
	    bignum/bignum_clear.c \
	    bignum/bignum_reserve.c \
	    bignum/bignum_resize.c \
	    bignum/bignum_copy.c \
	    bignum/bignum_dup.c \
	    bignum/bignum_move.c \
	    bignum/bignum_grow.c \
	    bignum/bignum_grow_front.c \
	    bignum/bignum_trunc.c \
	    bignum/bignum_zero.c \
	    bignum/bignum_one.c \
	    bignum/bignum_is_zero.c \
	    bignum/bignum_is_one.c \
	    bignum/bignum_is_word.c \
	    bignum/bignum_is_odd.c \
	    bignum/bignum_is_bit_set.c \
	    bignum/bignum_set_bit.c \
	    bignum/bignum_clear_bit.c \
	    bignum/bignum_lshift.c \
	    bignum/bignum_lshift_op.c \
	    bignum/bignum_rshift.c \
	    bignum/bignum_rshift_op.c \
	    bignum/bignum_lshift1.c \
	    bignum/bignum_lshift1_op.c \
	    bignum/bignum_rshift1.c \
	    bignum/bignum_rshift1_op.c \
	    bignum/bignum_rand_init.c \
	    bignum/bignum_rand_add.c \
	    bignum/bignum_rand_add_file.c \
	    bignum/bignum_rand_add_urandom.c \
	    bignum/bignum_rand_get.c \
	    bignum/bignum_rand.c \
	    bignum/bignum_rand_range.c \
	    bignum/bignum_cmp.c \
	    bignum/bignum_ucmp.c \
	    bignum/bignum_add.c \
	    bignum/bignum_add_op.c \
	    bignum/bignum_sub.c \
	    bignum/bignum_sub_op.c \
	    bignum/bignum_mul.c \
	    bignum/bignum_mul_op.c \
	    bignum/bignum_div_mod.c \
	    bignum/bignum_div_mod_op.c \
	    bignum/bignum_div.c \
	    bignum/bignum_mod.c \
	    bignum/bignum_mod_word.c \
	    bignum/bignum_exp.c \
	    bignum/bignum_exp_op.c \
	    bignum/bignum_mod_exp.c \
	    bignum/bignum_mod_exp_op.c \
	    bignum/bignum_gcd.c \
	    bignum/bignum_mod_inverse.c \
	    bignum/bignum_is_prime.c \
	    bignum/bignum_is_prime_fasttest.c \
	    bignum/bignum_is_prime_witness.c \
	    bignum/bignum_prime_checks_count.c \
	    bignum/bignum_num_bits.c \
	    bignum/bignum_num_bytes.c \
	    pem/pem_write_rsa_priv.c \
	    pem/pem_print_rsa_priv.c \
	    pem/pem_bignum.c \
	    pem/pem_len.c \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

LIBRARY = -L libft -lft

all: odir $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@echo " - Making $(NAME)"
	@$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $^ $(LIBRARY)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

odir:
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)utils
	@mkdir -p $(OBJS_PATH)hmac
	@mkdir -p $(OBJS_PATH)pbkdf2
	@mkdir -p $(OBJS_PATH)command
	@mkdir -p $(OBJS_PATH)hash
	@mkdir -p $(OBJS_PATH)base64
	@mkdir -p $(OBJS_PATH)des
	@mkdir -p $(OBJS_PATH)aes
	@mkdir -p $(OBJS_PATH)chacha20
	@mkdir -p $(OBJS_PATH)rc4
	@mkdir -p $(OBJS_PATH)camellia
	@mkdir -p $(OBJS_PATH)cipher
	@mkdir -p $(OBJS_PATH)rsa
	@mkdir -p $(OBJS_PATH)bignum
	@mkdir -p $(OBJS_PATH)pem

clean:
	@make -C libft clean
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@make -C libft fclean
	@echo " - Cleaning executable"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re odir
