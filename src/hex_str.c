/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:43:45 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 16:52:01 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*str2hex(const char *str)
{
	char	*result;
	int	len;
	int	i;

	len = ft_strlen(str);
	if (!(result = malloc(len * 2 + 1)))
		return (NULL);
	bin2hex(result, str, len);
	return (result);
}
