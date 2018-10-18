/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsautl_write_hex.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:03:02 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/18 12:51:02 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	to_hex(char c)
{
	if (c >= 10)
		return ('a' + c - 10);
	return ('0' + c);
}

static void	do_write_prev(t_rsautl_data *data)
{
	if (data->hex_pos % 16 == 8)
		ft_putchar_fd('-', data->fdout);
	else if (data->hex_pos % 16)
		ft_putchar_fd(' ', data->fdout);
	else
	{
		ft_putchar_fd(to_hex((data->hex_pos >> 12) & 0xf), data->fdout);
		ft_putchar_fd(to_hex((data->hex_pos >> 8) & 0xf), data->fdout);
		ft_putchar_fd(to_hex((data->hex_pos >> 4) & 0xf), data->fdout);
		ft_putchar_fd(to_hex((data->hex_pos >> 0) & 0xf), data->fdout);
		ft_putstr_fd(" - ", data->fdout);
	}
}

void		cmd_rsautl_write_hex(t_rsautl_data *data, uint8_t *ptr, int len)
{
	int	i;

	if (!data->hexdump)
	{
		write(data->fdout, ptr, len);
		return ;
	}
	i = 0;
	while (i < len)
	{
		do_write_prev(data);
		ft_putchar_fd(to_hex((ptr[i] >> 4) & 0xf), data->fdout);
		ft_putchar_fd(to_hex((ptr[i] >> 0) & 0xf), data->fdout);
		data->hex_line[data->hex_pos % 16] = ptr[i];
		data->hex_write = 1;
		if (++data->hex_pos % 16 == 0)
			cmd_rsautl_write_hex_line(data);
		++i;
	}
}

void		cmd_rsautl_write_hex_line(t_rsautl_data *data)
{
	int	i;

	if (!data->hex_write)
		return ;
	data->hex_write = 0;
	i = 6 + ((data->hex_pos + 15) % 16 + 1) * 3;
	while (++i < 6 + 4 + 16 * 3)
		ft_putchar_fd(' ', data->fdout);
	i = 0;
	while (i < ((data->hex_pos + 15) % 16) + 1)
	{
		if (ft_isprint(data->hex_line[i]))
			ft_putchar_fd(data->hex_line[i], data->fdout);
		else
			ft_putchar_fd('.', data->fdout);
		++i;
	}
	ft_putchar_fd('\n', data->fdout);
}
