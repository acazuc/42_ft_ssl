# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 06:50:12 by acazuc            #+#    #+#              #
#    Updated: 2018/07/05 20:14:16 by acazuc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ofast -mtune=native -g -rdynamic

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

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

LIBRARY = -L libft -lft

all: odir $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@echo " - Making $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBRARY)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

odir:
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)hash
	@mkdir -p $(OBJS_PATH)base64
	@mkdir -p $(OBJS_PATH)des
	@mkdir -p $(OBJS_PATH)cipher

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
