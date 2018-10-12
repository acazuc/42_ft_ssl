/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl_read.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:32:51 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/12 14:48:23 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_convert_bignum(t_rsautl_data *data, char *bdata, int readed
		, int len)
{
	if (readed == len + 1)
	{
		ft_putendl_fd("ft_ssl: input too long", 2);
		free(bdata);
		return (0);
	}
	if (!(data->bignum = bignum_bin2bignum((uint8_t*)bdata, readed, NULL)))
	{
		ft_putendl_fd("ft_ssl: failed to create bignum from input", 2);
		free(bdata);
		return (0);
	}
	free(bdata);
	if (bignum_ucmp(data->bignum, data->rsa_ctx.n) > 0)
	{
		ft_putendl_fd("ft_ssl: input too long", 2);
		return (0);
	}
	return (1);
}

int			cmd_rsautl_read(t_rsautl_data *data)
{
	char	*bdata;
	int		len;
	int		readed;

	if (!(len = bignum_num_bytes(data->rsa_ctx.n)))
	{
		ft_putendl_fd("ft_ssl: modulus length is 0 !", 2);
		return (0);
	}
	if (!(bdata = malloc(len + 1)))
	{
		ft_putendl_fd("ft_ssl: malloc failed", 2);
		return (0);
	}
	if ((readed = read(data->fdin, bdata, len + 1)) == -1)
	{
		ft_putendl_fd("ft_ssl: failed to read input", 2);
		free(bdata);
		return (0);
	}
	if (!do_convert_bignum(data, bdata, readed, len))
		return (0);
	return (1);
}
