/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:20:23 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 14:22:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGNUM_PROTOTYPES_H
# define BIGNUM_PROTOTYPES_H

int			bignum_print_fd(t_bignum *bignum, int fd);
int			bignum_print(t_bignum *bignum);
int			bignum_printhex_fd(t_bignum *bignum, int fd);
int			bignum_printhex(t_bignum *bignum);
int			bignum_dec2bignum(t_bignum *bignum, char *s);
int			bignum_hex2bignum(t_bignum *bignum, char *s);
uint32_t	bignum_npot(uint32_t val);
t_bignum	*bignum_new();
void		bignum_free(t_bignum *bignum);
void		bignum_init(t_bignum *bignum);
void		bignum_clear(t_bignum *bignum);
void		bignum_trunc(t_bignum *bignum);
int			bignum_grow(t_bignum *bignum, t_bignum_word a);
int			bignum_grow_front(t_bignum *bignum, t_bignum_word a);
void		bignum_zero(t_bignum *bignum);
int			bignum_one(t_bignum *bignum);
int			bignum_cmp(t_bignum *a, t_bignum *b);
int			bignum_ucmp(t_bignum *a, t_bignum *b);
int			bignum_is_zero(t_bignum *bignum);
int			bignum_is_one(t_bignum *bignum);
int			bignum_is_word(t_bignum *bignum, t_bignum_word word);
int			bignum_is_odd(t_bignum *bignum);
int			bignum_is_bit_set(t_bignum *a, uint32_t b);
int			bignum_set_bit(t_bignum *bignum, uint32_t n);
int			bignum_clear_bit(t_bignum *bignum, uint32_t n);
int			bignum_num_bits(t_bignum *bignum);
int			bignum_num_bytes(t_bignum *bignum);
int			bignum_reserve(t_bignum *bignum, uint32_t len);
int			bignum_resize(t_bignum *bignum, uint32_t len);
int			bignum_copy(t_bignum *dst, t_bignum *src);
t_bignum	*bignum_dup(t_bignum *bignum);
void		bignum_move(t_bignum *a, t_bignum *b);
int			bignum_lshift(t_bignum *r, t_bignum *a, uint32_t n);
int			bignum_lshift_op(t_bignum *r, t_bignum *a, uint32_t n);
int			bignum_rshift(t_bignum *r, t_bignum *a, uint32_t n);
int			bignum_rshift_op(t_bignum *r, t_bignum *a, uint32_t n);
int			bignum_lshift1(t_bignum *r, t_bignum *a);
int			bignum_lshift1_op(t_bignum *r, t_bignum *a);
int			bignum_rshift1(t_bignum *r, t_bignum *a);
int			bignum_rshift1_op(t_bignum *r, t_bignum *a);
void		bignum_rand_add(uint64_t init);
int			bignum_rand_add_file(char *file);
int			bignum_rand_add_urandom();
uint64_t	bignum_rand_get();
int			bignum_rand(t_bignum *bignum, uint32_t bits, int top, int bottom);
int			bignum_rand_range(t_bignum *bignum, t_bignum *range, int top
		, int bottom);
int			bignum_add(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_add_op(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_sub(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_sub_op(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_mul(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_mul_op(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_div_mod(t_bignum *dv, t_bignum *rm, t_bignum *a
		, t_bignum *b);
int			bignum_div_mod_op(t_bignum *dv, t_bignum *rm, t_bignum *a
		, t_bignum *b);
int			bignum_div(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_mod(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_mod_word(t_bignum_word *r, t_bignum *a, t_bignum_word b);
int			bignum_exp(t_bignum *r, t_bignum *a, t_bignum *p);
int			bignum_exp_op(t_bignum *r, t_bignum *a, t_bignum *p);
int			bignum_mod_exp(t_bignum *r, t_bignum *a, t_bignum *p, t_bignum *m);
int			bignum_mod_exp_op(t_bignum *r, t_bignum *a, t_bignum *p
		, t_bignum *m);
int			bignum_gcd(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_mod_inverse(t_bignum *r, t_bignum *a, t_bignum *b);
int			bignum_is_prime(t_bignum *bignum, uint32_t n, uint32_t *passed);
int			bignum_is_prime_witness(t_miller_ctx *ctx, t_bignum *bignum
		, uint32_t *passed);
int			bignum_is_prime_fasttest(t_bignum *bignun);
int			bignum_prime_checks_count(t_bignum *bignum);

#endif
