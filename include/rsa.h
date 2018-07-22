/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:27:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/22 15:05:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include "bignum.h"

typedef struct	s_rsa_prv
{
	t_bignum	*n;
	t_bignum	*d;
}		t_rsa_prv;

typedef struct	s_rsa_pub
{
	t_bignum	*n;
	t_bignum	*e;
}		t_rsa_pub;

typedef struct	s_rsa_ctx
{
	t_bignum	*p;
	t_bignum	*q;
	t_bignum	*d;
	t_bignum	*phi;
	t_bignum	*e;
	t_bignum	*n;
	t_bignum	*dmq;
	t_bignum	*dmp;
	t_bignum	*coef;
}		t_rsa_ctx;

int		rsa_genkey(t_rsa_ctx *ctx, uint64_t bits, int print);
int		rsa_genkey_pq(t_rsa_ctx *ctx, uint64_t bits, int print);
int		rsa_genkey_phi(t_rsa_ctx *ctx);
int		rsa_genkey_crt(t_rsa_ctx *ctx);

#endif
