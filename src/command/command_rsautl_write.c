/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl_write.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:56:05 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/17 20:01:59 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "pkcs1.5.h"

static void	do_reverse(uint8_t *data, int len)
{
	uint8_t	tmp;
	int		i;

	i = 0;
	while (i < len / 2)
	{
		tmp = data[i];
		data[i] = data[len - i - 1];
		data[len - i - 1] = tmp;
		++i;
	}
}

static int	do_build_bn_data_out(t_rsautl_data *data, uint8_t **bn_data
		, uint8_t **out, int len)
{
	if (!(*bn_data = malloc(len)))
	{
		ft_putendl_fd("ft_ssl: malloc failed", 2);
		return (0);
	}
	ft_memcpy(*bn_data, data->bignum->data, len);
	do_reverse(*bn_data, len);
	if (!(*out = malloc(len)))
	{
		free(*bn_data);
		ft_putendl_fd("ft_ssl: malloc failed", 2);
		return (0);
	}
	return (1);
}

static int	do_depad(t_rsautl_data *data)
{
	uint8_t	*bn_data;
	uint8_t	*out;
	int		len;
	int		outlen;

	len = bignum_num_bytes(data->bignum);
	if (!len)
	{
		ft_putendl_fd("ft_ssl: invalid input (bignum len is 0)", 2);
		return (0);
	}
	if (!do_build_bn_data_out(data, &bn_data, &out, len))
		return (0);
	if (!pkcs1_5_unpad(out, &outlen, bn_data, len))
	{
		free(bn_data);
		free(out);
		ft_putendl_fd("ft_ssl: pkcs1.5 depadding failed", 2);
		return (0);
	}
	outlen = write(data->fdout, out, outlen);
	free(bn_data);
	free(out);
	return (1);
}

int			cmd_rsautl_write(t_rsautl_data *data)
{
	int	len;
	int	i;
	int	osef;

	if (data->mode == RSAUTL_MODE_DECRYPT || data->mode == RSAUTL_MODE_VERIFY)
		return (do_depad(data));
	len = bignum_num_bytes(data->bignum);
	i = 0;
	while (i < len)
	{
		osef = write(data->fdout, ((uint8_t*)data->bignum->data) + len - 1 - i, 1);
		++i;
	}
	(void)osef;
	return (1);
}
