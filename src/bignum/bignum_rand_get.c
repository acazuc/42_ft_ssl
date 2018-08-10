/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_rand_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:59:14 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 21:27:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"
#include "sha1.h"

uint64_t	g_bignum_rand;

uint64_t	bignum_rand_get()
{
	t_sha1_ctx	ctx;
	uint8_t		digest[20];

	g_bignum_rand = g_bignum_rand * 6364136223846793005ull
				+ 1442695040888963407ull;
	sha1_init(&ctx);
	sha1_update(&ctx, (uint8_t*)&g_bignum_rand, sizeof(g_bignum_rand));
	sha1_final(digest, &ctx);
	return (*(uint64_t*)digest);
}
