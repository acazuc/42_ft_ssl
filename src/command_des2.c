/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_des2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 19:10:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/04 15:27:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	command_des2(int ac, char **av, t_des_data *data)
{
	data->ctx2.nopad = 1;
	data->ctx3.nopad = 1;
	(void)ac;
	(void)av;
	(void)data;
	return (EXIT_SUCCESS);
}
