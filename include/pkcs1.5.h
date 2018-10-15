/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pkcs1.5.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 10:59:01 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/15 11:25:53 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PKCS_1_5_H
# define PKCS_1_5_H

# include <stdint.h>

int			pkcs1_5_pad(uint8_t *out, int outlen, uint8_t *in, int inlen);
int			pkcs1_5_unpad(uint8_t *out, int *outlen, uint8_t *in, int inlen);

#endif
