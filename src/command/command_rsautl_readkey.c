/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl_readkey.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:38:17 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 14:49:00 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

int	cmd_rsautl_readkey(t_rsautl_data *data)
{
	if (data->pubin)
	{
		if (!pem_read_rsa_pub_file(&data->rsa_ctx, data->keyfd, data->passin))
			return (0);
	}
	else
	{
		if (!pem_read_rsa_priv_file(&data->rsa_ctx, data->keyfd, data->passin))
			return (0);
	}
	return (1);
}
