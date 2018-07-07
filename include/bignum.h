/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:19:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 10:18:27 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGNUM_H
# define BIGNUM_H

# include "libft.h"
# include <stdint.h>

typedef struct		s_bignum
{
	uint32_t	*data;
	uint64_t	cap;
	uint64_t	len;
}			t_bignum;

void		bignum_print_fd(t_bignum *bignum, int fd);
void		bignum_print(t_bignum *bignum);
uint64_t	bignum_npot(uint64_t val);
t_bignum	*bignum_new();
void		bignum_free(t_bignum *bignum);
void		bignum_trunc(t_bignum *bignum);
int		bignum_grow(t_bignum *bignum, uint32_t a);
int		bignum_grow_front(t_bignum *bignum, uint32_t a);
void		bignum_zero(t_bignum *bignum);
int		bignum_one(t_bignum *bignum);
int		bignum_cmp(t_bignum *a, t_bignum *b);
int		bignum_is_zero(t_bignum *bignum);
int		bignum_is_one(t_bignum *bignum);
int		bignum_is_word(t_bignum *bignum, uint32_t word);
int		bignum_is_odd(t_bignum *bignum);
int		bignum_reserve(t_bignum *bignum, uint64_t len);
int		bignum_resize(t_bignum *bignum, uint64_t len);
int		bignum_copy(t_bignum *dst, t_bignum *src);
t_bignum	*bignum_dup(t_bignum *bignum);
int		bignum_lshift(t_bignum *r, t_bignum *a, uint64_t n);
int		bignum_rshift(t_bignum *r, t_bignum *a, uint64_t n);
int		bignum_lshift1(t_bignum *r, t_bignum *a);
int		bignum_rshift1(t_bignum *r, t_bignum *a);
int		bignum_rand(t_bignum *bignum, uint64_t bits);
int		bignum_div_mod(t_bignum *dv, t_bignum *rm, t_bignum *a, t_bignum *b);
int		bignum_add(t_bignum *r, t_bignum *a, t_bignum *b);
int		bignum_sub(t_bignum *r, t_bignum *a, t_bignum *b);
int		bignum_mul(t_bignum *r, t_bignum *a, t_bignum *b);
int		bignum_div(t_bignum *r, t_bignum *a, t_bignum *b);
int		bignum_mod(t_bignum *r, t_bignum *a, t_bignum *b);
int		bignum_exp(t_bignum *r, t_bignum *a, t_bignum *b);
int		bignum_gcd(t_bignum *r, t_bignum *a, t_bignum *b);

#define BIGNUM_BASE (1000000000U)

#endif
