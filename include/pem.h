/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:46:47 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:00:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PEM_H
# define PEM_H

# include <stdint.h>
# include "vecu8.h"

typedef struct	s_rsa_ctx t_rsa_ctx;

uint32_t	pem_len_len(uint32_t len);
uint32_t	pem_write_len(uint8_t *data, uint32_t len);
int32_t		pem_read_len(uint8_t *data, uint32_t len, uint32_t *result);
uint32_t	pem_bignum_len(t_bignum *bignum);
int		pem_write_bignum(t_vecu8 *data, t_bignum *bignum);
int		pem_write_rsa_priv(char **dst, t_rsa_ctx *ctx);

#endif
