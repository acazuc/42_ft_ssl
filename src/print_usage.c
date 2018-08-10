/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:19:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/10 23:09:39 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_usage()
{
	ft_putendl("usage: ft_ssl command [command options] [commands args]\n");
	print_usage_commands();
}

static void	print_commands_standard()
{
	ft_putendl("Standard commands:");
	ft_putendl("genrsa\trsa\trsautl");
}

static void	print_commands_md()
{
	ft_putendl("Message digest commands:");
	ft_putendl("md5\tsha1\tsha224");
	ft_putendl("sha256\tsha384\tsha512");
}

static void	print_commands_ciphers()
{
	ft_putendl("Cipher commands:");
	ft_putendl("base64");
	ft_putendl("des\t\tdes-ecb\t\tdes-cbc");
	ft_putendl("des-fcbc\tdes-cfb\t\tdes-ofb");
	ft_putendl("des2\t\tdes2-ecb\tdes2-cbc");
	ft_putendl("des2-fcbc\tdes2-cfb\tdes2-ofb");
	ft_putendl("des3\t\tdes3-ecb\tdes3-cbc");
	ft_putendl("des3-fcbc\tdes3-cfb\tdes3-ofb");
	ft_putendl("aes-128\t\taes-128-ecb\taes-128-cbc");
	ft_putendl("aes-128-fcbc\taes-128-cfb\taes-128-ofb");
	ft_putendl("aes-192\t\taes-192-ecb\taes-192-cbc");
	ft_putendl("aes-192-fcbc\taes-192-cfb\taes-192-ofb");
	ft_putendl("aes-256\t\taes-256-ecb\taes-256-cbc");
	ft_putendl("aes-256-fcbc\taes-256-cfb\taes-256-ofb");
}

void		print_usage_commands()
{
	print_commands_standard();
	ft_putchar('\n');
	print_commands_md();
	ft_putchar('\n');
	print_commands_ciphers();
}
