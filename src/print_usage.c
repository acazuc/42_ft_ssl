/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:19:00 by acazuc            #+#    #+#             */
/*   Updated: 2019/08/04 14:43:25 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		print_usage(void)
{
	ft_putendl("usage: ft_ssl command [command options] [commands args]\n");
	print_usage_commands();
}

static void	print_commands_standard(void)
{
	ft_putendl("Standard commands:");
	ft_putendl("genrsa\trsa\trsautl");
}

static void	print_commands_md(void)
{
	ft_putendl("Message digest commands:");
	ft_putendl("md4\t\tmd5\t\tsha1");
	ft_putendl("sha224\t\tsha256\t\tsha384");
	ft_putendl("sha512\t\tripemd128\tripemd160");
	ft_putendl("ripemd256\tripemd320\tcrc32");
	ft_putendl("adler32");
}

static void	print_commands_ciphers(void)
{
	ft_putendl("Cipher commands:");
	ft_putendl("base64");
	ft_putendl("des\t\t\tdes-ecb\t\t\tdes-cbc");
	ft_putendl("des-fcbc\t\tdes-cfb\t\t\tdes-ofb");
	ft_putendl("des2\t\t\tdes2-ecb\t\tdes2-cbc");
	ft_putendl("des2-fcbc\t\tdes2-cfb\t\tdes2-ofb");
	ft_putendl("des3\t\t\tdes3-ecb\t\tdes3-cbc");
	ft_putendl("des3-fcbc\t\tdes3-cfb\t\tdes3-ofb");
	ft_putendl("aes-128\t\t\taes-128-ecb\t\taes-128-cbc");
	ft_putendl("aes-128-fcbc\t\taes-128-cfb\t\taes-128-ofb");
	ft_putendl("aes-192\t\t\taes-192-ecb\t\taes-192-cbc");
	ft_putendl("aes-192-fcbc\t\taes-192-cfb\t\taes-192-ofb");
	ft_putendl("aes-256\t\t\taes-256-ecb\t\taes-256-cbc");
	ft_putendl("aes-256-fcbc\t\taes-256-cfb\t\taes-256-ofb");
	ft_putendl("camellia-128\t\tcamellia-128-ecb\tcamellia-128-cbc");
	ft_putendl("camellia-128-fcbc\tcamellia-128-cfb\tcamellia-128-ofb");
	ft_putendl("camellia-192\t\tcamellia-192-ecb\tcamellia-192-cbc");
	ft_putendl("camellia-192-fcbc\tcamellia-192-cfb\tcamellia-192-ofb");
	ft_putendl("camellia-256\t\tcamellia-256-ecb\tcamellia-256-cbc");
	ft_putendl("camellia-256-fcbc\tcamellia-256-cfb\tcamellia-256-ofb");
	ft_putendl("aria-128\t\taria-128-ecb\t\taria-128-cbc");
	ft_putendl("aria-128-fcbc\t\taria-128-cfb\t\taria-128-ofb");
	ft_putendl("aria-192\t\taria-192-ecb\t\taria-192-cbc");
	ft_putendl("aria-192-fcbc\t\taria-192-cfb\t\taria-192-ofb");
	ft_putendl("aria-256\t\taria-256-ecb\t\taria-256-cbc");
	ft_putendl("aria-256-fcbc\t\taria-256-cfb\t\taria-256-ofb");
	ft_putendl("chacha20\t\trc4");
}

void		print_usage_commands(void)
{
	print_commands_standard();
	ft_putchar('\n');
	print_commands_md();
	ft_putchar('\n');
	print_commands_ciphers();
}
