/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:22:13 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/11 16:07:58 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGNUM_STRUCTS_H
# define BIGNUM_STRUCTS_H

typedef uint64_t	t_bignum_word;
typedef int64_t		t_bignum_sword;
typedef __uint128_t	t_bignum_dword;
typedef __int128_t	t_bignum_sdword;

typedef struct		s_bignum
{
	t_bignum_word	*data;
	uint32_t		cap;
	uint32_t		len;
	int				sign;
}					t_bignum;

typedef struct		s_miller_ctx
{
	t_bignum		a;
	t_bignum		n1;
	t_bignum		d;
	int				s;
}					t_miller_ctx;

typedef struct		s_mod_inv_ctx
{
	t_bignum		*a;
	t_bignum		*b;
	t_bignum		q;
	t_bignum		r;
	t_bignum		s;
	t_bignum		old_r;
	t_bignum		old_s;
	t_bignum		tmp;
}					t_mod_inv_ctx;

#endif
