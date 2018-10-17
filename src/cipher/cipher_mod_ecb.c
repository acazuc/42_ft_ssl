/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_mod_ecb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 21:25:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/17 19:56:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/cipher.h"

t_cipher_mod	g_cipher_mod_ecb = {cipher_ecb_premod, cipher_ecb_postmod
	, 0, 0};
t_cipher_mod	g_cipher_mod_ecb_nopad = {cipher_ecb_premod,
	cipher_ecb_postmod, 1, 0};

void	cipher_ecb_premod(t_cipher_ctx *ctx, uint8_t *data)
{
	(void)ctx;
	(void)data;
}

void	cipher_ecb_postmod(t_cipher_ctx *ctx, uint8_t *data)
{
	(void)ctx;
	(void)data;
}
