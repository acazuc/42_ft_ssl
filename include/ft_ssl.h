/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/09 13:45:11 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "cipher/cipher.h"
# include "hash/hash.h"
# include "base64.h"
# include "libft.h"
# include "rsa.h"
# include <stdint.h>
# include <math.h>

# include "ft_ssl_structs.h"
# include "ft_ssl_prototypes.h"

# define FT_MIN(a, b) (a < b ? a : b)
# define FT_MAX(a, b) (a > b ? a : b)

#endif
