/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:19:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/04 20:30:56 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_usage()
{
	ft_putendl("usage: ft_ssl command [command options] [commands args]");
	print_usage_commands();
}

static void	print_commands_md()
{
	ft_putendl("Message digest commands:");
	ft_putendl("md5");
	ft_putendl("sha1");
	ft_putendl("sha224");
	ft_putendl("sha256");
	ft_putendl("sha384");
	ft_putendl("sha512");
}

static void	print_commands_ciphers()
{
	ft_putendl("Cipher commands:");
	ft_putendl("base64");
	ft_putendl("des");
	ft_putendl("des-ecb");
	ft_putendl("des-cbc");
	ft_putendl("des-fcbc");
	ft_putendl("des-cfb");
	ft_putendl("des-ofb");
	ft_putendl("des2");
	ft_putendl("des2-ecb");
	ft_putendl("des2-cbc");
	ft_putendl("des2-fcbc");
	ft_putendl("des2-cfb");
	ft_putendl("des2-ofb");
	ft_putendl("des3");
	ft_putendl("des3-ecb");
	ft_putendl("des3-cbc");
	ft_putendl("des3-fcbc");
	ft_putendl("des3-cfb");
	ft_putendl("des3-ofb");
}

void		print_usage_commands()
{
	print_commands_md();
	ft_putendl("");
	print_commands_ciphers();
}
