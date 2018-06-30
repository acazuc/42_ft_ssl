/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/30 21:11:28 by acazuc           ###   ########.fr       */
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
	else if (!ft_strcmp(av[1], "sha224"))
		return (command_sha224(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "sha256"))
		return (command_sha256(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "sha384"))
		return (command_sha384(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "sha512"))
		return (command_sha512(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "base64"))
		return (command_base64(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des"))
		return (command_des(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ecb"))
		return (command_des_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-cbc"))
		return (command_des_cbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-pcbc"))
		return (command_des_pcbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-cfb"))
		return (command_des_cfb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ofb"))
		return (command_des_ofb(ac - 2, av + 2));
	else
	{
		ft_putstr("ft_ssl: invalid command: ");
		ft_putendl(av[1]);
		print_usage_commands();
		return (EXIT_FAILURE);
	}
}
