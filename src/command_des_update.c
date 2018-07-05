/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:17:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/05 13:25:35 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	do_update_part(t_des_data *data, uint64_t *buf, int len)
{
	data->premod(data, buf);
	if (data->mode)
	{
		if (!des_decrypt_update(&data->ctx[0], buf, len))
			return (0);
	}
	else
	{
		if (!des_encrypt_update(&data->ctx[0], buf, len))
			return (0);
	}
	data->postmod(data, buf);
	cmd_des_callback(data, buf, len);
	return (1);
}

static void	do_pad(t_des_data *data, uint8_t *buf, int *total)
{
	uint8_t	pad;
	int	i;

	if (data->mode || data->nopad)
		return ;
	pad = 8 - *total;
	if (pad == 0)
	{
		i = -1;
		while (++i < 8)
			buf[i] = 8;
	}
	else
	{
		i = *total - 1;
		while (++i < 8)
			buf[i] = pad;
	}
	*total = 8;
}

static	int	do_loop(t_des_data *data, uint8_t *buf, int *total)
{
	int	tmp;

	tmp = 0;
	while (*total - tmp >= (data->mode ? 9 : 8))
	{
		if (!do_update_part(data, (uint64_t*)(buf + tmp), 8))
			return (0);
		tmp += 8;
	}
	while (*total >= (data->mode ? 9 : 8))
		*total -= 8;
	memcpy(buf, buf + tmp, *total);
	return (1);
}

int		cmd_des_do_update(t_des_data *data)
{
	uint8_t	buf[4096];
	int	total;
	int	ret;

	data->ended = 0;
	total = 0;
	while ((ret = read(data->fdin, buf + total, 4096 - total)) > 0)
	{
		total += ret;
		if (!do_loop(data, buf, &total))
		{
			ret = -1;
			break;
		}
	}
	data->ended = 1;
	do_pad(data, buf, &total);
	if (ret == -1 || (total && !do_update_part(data, (uint64_t*)buf, total)))
	{
		ft_putendl_fd("ft_ssl: error while reading input", 2);
		return (0);
	}
	return (1);
}
