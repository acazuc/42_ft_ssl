/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcs1.5.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:59:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/16 10:25:38 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PKCS1_5_H
# define PKCS1_5_H

# include <stdint.h>

int			pkcs1_5_pad(uint8_t *out, int outlen, uint8_t *in, int inlen);
int			pkcs1_5_unpad(uint8_t *out, int *outlen, uint8_t *in, int inlen);

#endif
