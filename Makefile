# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 06:50:12 by acazuc            #+#    #+#              #
#    Updated: 2018/07/22 17:41:24 by acazuc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc

LDFLAGS = -flto=4

CFLAGS = -Wall -Wextra -Werror -Ofast -mtune=native -g -rdynamic
#CFLAGS+= -fsanitize=address
CFLAGS+= -flto

INCLUDES = -I include/ -I libft/include

SRCS_PATH = src/

SRCS_NAME = main.c \
	    print_usage.c \
	    rotate_left.c \
	    rotate_right.c \
	    hex_bin.c \
	    random_bytes.c \
	    hmac.c \
	    pbkdf2.c \
	    command_hash.c \
	    command_md5.c \
	    command_sha1.c \
	    command_sha224.c \
	    command_sha256.c \
	    command_sha384.c \
	    command_sha512.c \
	    command_base64.c \
	    command_des1.c \
	    command_des1_ciphers.c \
	    command_des2.c \
	    command_des2_ciphers.c \
	    command_des3.c \
	    command_des3_ciphers.c \
	    command_des_common1.c \
	    command_des_execute.c \
	    command_des_args.c \
	    command_des_callback.c \
	    command_des_initfree.c \
	    command_bignum.c \
	    command_genrsa.c \
	    command_genrsa2.c \
	    hash/md5.c \
	    hash/sha1.c \
	    hash/sha224.c \
	    hash/sha256.c \
	    hash/sha384.c \
	    hash/sha512.c \
	    base64/base64_encode.c \
	    base64/base64_decode.c \
	    des/des.c \
	    des/des_encrypt.c \
	    des/des_decrypt.c \
	    cipher/cipher.c \
	    cipher/cipher_update.c \
	    cipher/cipher_mod_ecb.c \
	    cipher/cipher_mod_cbc.c \
	    cipher/cipher_mod_pcbc.c \
	    cipher/cipher_mod_cfb.c \
	    cipher/cipher_mod_ofb.c \
	    rsa/rsa_genkey.c \
	    rsa/rsa_genkey_pq.c \
	    rsa/rsa_genkey_phi.c \
	    rsa/rsa_genkey_crt.c \
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
	@mkdir -p $(OBJS_PATH)hash
	@mkdir -p $(OBJS_PATH)base64
	@mkdir -p $(OBJS_PATH)des
	@mkdir -p $(OBJS_PATH)cipher
	@mkdir -p $(OBJS_PATH)rsa
	@mkdir -p $(OBJS_PATH)bignum

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
