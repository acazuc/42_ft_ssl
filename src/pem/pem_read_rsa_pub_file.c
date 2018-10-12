/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pem_read_rsa_pub_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 10:14:09 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 14:11:48 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pem.h"

int	pem_read_rsa_pub_file(t_rsa_ctx *ctx, int fd, char *password)
{
	/*while (readed > 0 && total_readed < strlen(BEGIN_TEXT))
	{
	}
	if (total_readed < strlen(BEGIN_TEXT))
		return (0);
	if (ft_memcpy(data, BEGIN_TEXT, strlen(BEGIN_TEXT)))
		return (0);
	if (!read_data(ctx, fd))
		return (0);
	while (readed > 0 && total_readed < strlen(END_TEXT))
	{
	}
	//check if \n at the end
	if (total_readed != strlen(END_TEXT))
		return (0);
	if (ft_memcpy(data, END_TEXT, strlen(END_TEXT)))
		return (0);*/
	(void)ctx;
	(void)fd;
	(void)password;
	return (1);
}
