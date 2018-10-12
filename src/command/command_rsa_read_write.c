/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa_read_write.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:35:39 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 12:58:22 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pem.h"

int	cmd_rsa_read(t_rsa_data *data)
{
	if (data->pubin)
	{
		if (!pem_read_rsa_pub_file(&data->rsa_ctx, data->fdin, data->passin))
			return (0);
	}
	else
	{
		if (!pem_read_rsa_priv_file(&data->rsa_ctx, data->fdin, data->passin))
			return (0);
	}
	return (1);
}

int	cmd_rsa_write(t_rsa_data *data)
{
	if (data->pubout)
	{
		if (!pem_write_rsa_pub_file(&data->rsa_ctx, data->fdout, data->cipher_name, data->passout))
			return (0);
	}
	else
	{
		if (!pem_write_rsa_priv_file(&data->rsa_ctx, data->fdout, data->cipher_name, data->passout))
			return (0);
	}
	return (1);
}
