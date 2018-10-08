/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 20:35:15 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:48:03 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cipher/camellia.h"
#include "cipher/chacha20.h"
#include "cipher/des.h"
#include "cipher/aes.h"
#include "cipher/rc4.h"
#include "libft.h"

static t_cipher	*cipher_get_des(char *name)
{
	CIPHER_GET_TEST(g_cipher_des1_ecb, name);
	CIPHER_GET_TEST(g_cipher_des1_cbc, name);
	CIPHER_GET_TEST(g_cipher_des1_pcbc, name);
	CIPHER_GET_TEST(g_cipher_des1_cfb, name);
	CIPHER_GET_TEST(g_cipher_des1_ofb, name);
	CIPHER_GET_TEST(g_cipher_des1_ctr, name);
	CIPHER_GET_TEST(g_cipher_des2_ecb, name);
	CIPHER_GET_TEST(g_cipher_des2_cbc, name);
	CIPHER_GET_TEST(g_cipher_des2_pcbc, name);
	CIPHER_GET_TEST(g_cipher_des2_cfb, name);
	CIPHER_GET_TEST(g_cipher_des2_ofb, name);
	CIPHER_GET_TEST(g_cipher_des2_ctr, name);
	CIPHER_GET_TEST(g_cipher_des3_ecb, name);
	CIPHER_GET_TEST(g_cipher_des3_cbc, name);
	CIPHER_GET_TEST(g_cipher_des3_pcbc, name);
	CIPHER_GET_TEST(g_cipher_des3_cfb, name);
	CIPHER_GET_TEST(g_cipher_des3_ofb, name);
	CIPHER_GET_TEST(g_cipher_des3_ctr, name);
	return (NULL);
}

static t_cipher	*cipher_get_aes(char *name)
{
	CIPHER_GET_TEST(g_cipher_aes128_ecb, name);
	CIPHER_GET_TEST(g_cipher_aes128_cbc, name);
	CIPHER_GET_TEST(g_cipher_aes128_pcbc, name);
	CIPHER_GET_TEST(g_cipher_aes128_cfb, name);
	CIPHER_GET_TEST(g_cipher_aes128_ofb, name);
	CIPHER_GET_TEST(g_cipher_aes128_ctr, name);
	CIPHER_GET_TEST(g_cipher_aes192_ecb, name);
	CIPHER_GET_TEST(g_cipher_aes192_cbc, name);
	CIPHER_GET_TEST(g_cipher_aes192_pcbc, name);
	CIPHER_GET_TEST(g_cipher_aes192_cfb, name);
	CIPHER_GET_TEST(g_cipher_aes192_ofb, name);
	CIPHER_GET_TEST(g_cipher_aes192_ctr, name);
	CIPHER_GET_TEST(g_cipher_aes256_ecb, name);
	CIPHER_GET_TEST(g_cipher_aes256_cbc, name);
	CIPHER_GET_TEST(g_cipher_aes256_pcbc, name);
	CIPHER_GET_TEST(g_cipher_aes256_cfb, name);
	CIPHER_GET_TEST(g_cipher_aes256_ofb, name);
	CIPHER_GET_TEST(g_cipher_aes256_ctr, name);
	return (NULL);
}

static t_cipher	*cipher_get_camellia(char *name)
{
	CIPHER_GET_TEST(g_cipher_camellia128_ecb, name);
	CIPHER_GET_TEST(g_cipher_camellia128_cbc, name);
	CIPHER_GET_TEST(g_cipher_camellia128_pcbc, name);
	CIPHER_GET_TEST(g_cipher_camellia128_cfb, name);
	CIPHER_GET_TEST(g_cipher_camellia128_ofb, name);
	CIPHER_GET_TEST(g_cipher_camellia128_ctr, name);
	CIPHER_GET_TEST(g_cipher_camellia192_ecb, name);
	CIPHER_GET_TEST(g_cipher_camellia192_cbc, name);
	CIPHER_GET_TEST(g_cipher_camellia192_pcbc, name);
	CIPHER_GET_TEST(g_cipher_camellia192_cfb, name);
	CIPHER_GET_TEST(g_cipher_camellia192_ofb, name);
	CIPHER_GET_TEST(g_cipher_camellia192_ctr, name);
	CIPHER_GET_TEST(g_cipher_camellia256_ecb, name);
	CIPHER_GET_TEST(g_cipher_camellia256_cbc, name);
	CIPHER_GET_TEST(g_cipher_camellia256_pcbc, name);
	CIPHER_GET_TEST(g_cipher_camellia256_cfb, name);
	CIPHER_GET_TEST(g_cipher_camellia256_ofb, name);
	CIPHER_GET_TEST(g_cipher_camellia256_ctr, name);
	return (NULL);
}

t_cipher		*cipher_get(char *name)
{
	t_cipher	*tmp;

	if ((tmp = cipher_get_des(name)))
		return (tmp);
	if ((tmp = cipher_get_aes(name)))
		return (tmp);
	if ((tmp = cipher_get_camellia(name)))
		return (tmp);
	CIPHER_GET_TEST(g_cipher_chacha20, name);
	CIPHER_GET_TEST(g_cipher_rc4, name);
	return (NULL);
}
