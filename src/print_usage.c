/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:19:00 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 16:22:34 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_usage()
{
	ft_putendl("usage: ft_ssl command [command options] [commands args]");
}

void	print_usage_commands()
{
	ft_putendl("Message digest commands:");
	ft_putendl("md5");
	ft_putendl("sha1");
	ft_putendl("sha224");
	ft_putendl("sha256");
	ft_putendl("sha384");
	ft_putendl("sha512");
	ft_putendl("");
	ft_putendl("Cipher commands:");
	ft_putendl("base64");
	ft_putendl("des");
}
