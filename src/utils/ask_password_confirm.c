/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_password_confirm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:28:46 by acazuc            #+#    #+#             */
/*   Updated: 2019/03/03 18:09:12 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*ask_password_confirm(void)
{
	char	*pass;
	char	*tmp;

	if (!(tmp = getpass("Enter cipher password: ")))
		return (NULL);
	if (!(pass = ft_strdup(tmp)))
		return (NULL);
	if (!(tmp = getpass("Verifying - Enter cipher password: ")))
	{
		free(pass);
		return (NULL);
	}
	if (ft_strcmp(tmp, pass))
	{
		ft_putendl_fd("Password are not the same", 2);
		free(pass);
		return (NULL);
	}
	free(pass);
	return (tmp);
}
