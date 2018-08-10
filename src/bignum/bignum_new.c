/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:23:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 18:43:45 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"
#include <stdlib.h>

t_bignum	*bignum_new()
{
	t_bignum	*result;

	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	bignum_init(result);
	return (result);
}
