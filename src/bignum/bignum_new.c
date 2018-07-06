/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 11:23:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/06 19:09:08 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bignum.h"

t_bignum	*bignum_new()
{
	t_bignum	*result;

	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	result->len = 0;
	result->cap = 0;
	result->data = NULL;
	return (result);
}
