/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 15:27:10 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/08 15:47:53 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include "bignum.h"

typedef struct	s_rsa_ctx
{
	t_bignum	*p;
	t_bignum	*q;
	t_bignum	*n;
	t_bignum	*e;
	t_bignum	*d;
}		t_rsa_ctx;

#endif
