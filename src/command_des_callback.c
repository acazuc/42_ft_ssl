/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 21:57:19 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 12:02:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	cmd_des_callback(t_des_data *ctx, uint64_t *data, size_t len)
{
	if (ctx->mode && ctx->ended && !ctx->nopad)
	{
		if (((char*)data)[7] > 8)
			return (0);
		len -= ((char*)data)[7];
	}
	len = write(ctx->fdout, data, len);
	return (1);
}
