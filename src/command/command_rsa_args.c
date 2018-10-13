/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rsa_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 10:39:24 by acazuc            #+#    #+#             */
/*   Updated: 2018/10/13 12:47:31 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	cmd_rsa_args3(t_rsa_data *data, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-des"))
		data->cipher_name = "DES-CBC";
	else if (!ft_strcmp(av[*i], "-des2"))
		data->cipher_name = "DES-EDE-CBC";
	else if (!ft_strcmp(av[*i], "-des3"))
		data->cipher_name = "DES-EDE3-CBC";
	else if (!ft_strcmp(av[*i], "-aes128"))
		data->cipher_name = "AES-128-CBC";
	else if (!ft_strcmp(av[*i], "-aes192"))
		data->cipher_name = "AES-192-CBC";
	else if (!ft_strcmp(av[*i], "-aes256"))
		data->cipher_name = "AES-256-CBC";
	else if (!ft_strcmp(av[*i], "-camellia128"))
		data->cipher_name = "CAMELLIA-128-CBC";
	else if (!ft_strcmp(av[*i], "-camellia192"))
		data->cipher_name = "CAMELLIA-192-CBC";
	else if (!ft_strcmp(av[*i], "-camellia256"))
		data->cipher_name = "CAMELLIA-256-CBC";
	else
	{
		ft_putstr_fd("ft_ssl: unexpected argument: ", 2);
		ft_putendl_fd(av[*i], 2);
		return (0);
	}
	return (1);
}

static int	cmd_rsa_args2(t_rsa_data *data, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-in"))
	{
		if (!cmd_rsa_handle_in(data, ac, av, i))
			return (0);
	}
	else if (!ft_strcmp(av[*i], "-out"))
	{
		if (!cmd_rsa_handle_out(data, ac, av, i))
			return (0);
	}
	else if (!ft_strcmp(av[*i], "-text"))
		data->print_text = 1;
	else if (!ft_strcmp(av[*i], "-modulus"))
		data->print_modulus = 1;
	else if (!ft_strcmp(av[*i], "-noout"))
		data->noout = 1;
	else if (!ft_strcmp(av[*i], "-check"))
		data->check = 1;
	else if (!cmd_rsa_args3(data, av, i))
		return (0);
	return (1);
}

int			cmd_rsa_args(t_rsa_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-inform") || !ft_strcmp(av[i], "-outform"))
		{
			if (!cmd_rsa_handle_inform_outform(data, ac, av, &i))
				return (0);
		}
		else if (!ft_strcmp(av[i], "-passin") || !ft_strcmp(av[i], "-passout"))
		{
			if (!cmd_rsa_handle_passin_passout(data, ac, av, &i))
				return (0);
		}
		else if (!ft_strcmp(av[i], "-pubin"))
			data->pubin = 1;
		else if (!ft_strcmp(av[i], "-pubout"))
			data->pubout = 1;
		else if (!cmd_rsa_args2(data, ac, av, &i))
			return (0);
		++i;
	}
	return (1);
}
