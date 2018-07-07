/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/07/07 22:19:10 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"

static int	handle_3(int ac, char **av)
{
	if (!ft_strcmp(av[1], "des-ede3-ofb"))
		return (command_des3_ofb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "bignum"))
		return (command_bignum(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "genrsa"))
		return (command_genrsa(ac - 2, av + 2));
	ft_putstr("ft_ssl: invalid command: ");
	ft_putendl(av[1]);
	print_usage_commands();
	return (EXIT_FAILURE);
}

static int	handle_2(int ac, char **av)
{
	if (!ft_strcmp(av[1], "des-ofb"))
		return (command_des_ofb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede"))
		return (command_des2_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede-ecb"))
		return (command_des2_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede-cbc"))
		return (command_des2_cbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede-pcbc"))
		return (command_des2_pcbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede-cfb"))
		return (command_des2_cfb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede-ofb"))
		return (command_des2_ofb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede3"))
		return (command_des3_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede3-ecb"))
		return (command_des3_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede3-cbc"))
		return (command_des3_cbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede3-pcbc"))
		return (command_des3_pcbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ede3-cfb"))
		return (command_des3_cfb(ac - 2, av + 2));
	return (handle_3(ac, av));
}

static int	handle_1(int ac, char **av)
{
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
		return (command_des_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-ecb"))
		return (command_des_ecb(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-cbc"))
		return (command_des_cbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-pcbc"))
		return (command_des_pcbc(ac - 2, av + 2));
	else if (!ft_strcmp(av[1], "des-cfb"))
		return (command_des_cfb(ac - 2, av + 2));
	return (handle_2(ac, av));
}

int		main(int ac, char **av)
{
	if (ac < 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	return (handle_1(ac, av));
}
