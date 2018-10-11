/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 19:31:35 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 19:37:19 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_H
# define HMAC_H

# include <stdint.h>

typedef struct s_hash_ctx	t_hash_ctx;

typedef struct		s_hmac_ctx
{
	t_hash_ctx		h;
	uint8_t			*key;
	uint32_t		key_len;
	uint8_t			*msg;
	uint32_t		msg_len;
}					t_hmac_ctx;

uint8_t		*hmac(t_hmac_ctx *ctx);

#endif
