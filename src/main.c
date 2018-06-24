/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 09:31:09 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(av[1], "md5"))
		return (command_md5(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "sha1"))
		return (command_sha1(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "sha256"))
		return (command_sha256(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "sha512"))
		return (command_sha512(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "base64"))
		return (command_base64(ac - 2, av + 2));
	else
	{
		ft_putstr("ft_ssl: invalid command: ");
		ft_putendl(av[1]);
		print_usage_commands();
		return (EXIT_FAILURE);
	}
}
