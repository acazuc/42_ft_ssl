/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:23:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/08 13:58:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stdlib.h>

t_bignum	*bignum_new(void)
{
	t_bignum	*result;

	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	bignum_init(result);
	return (result);
}
