/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:32:21 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 14:51:13 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PBKDF2_H
# define PBKDF2_H

# include <stdint.h>

typedef struct s_hash_ctx	t_hash_ctx;

typedef struct		s_pbkdf2_ctx
{
	t_hash_ctx		h;
	uint8_t			*password;
	uint32_t		password_len;
	uint8_t			*salt;
	uint32_t		salt_len;
	uint32_t		iterations;
	uint8_t			*out;
	uint32_t		out_len;
}					t_pbkdf2_ctx;

int					pbkdf2(t_pbkdf2_ctx *ctx);

#endif
