/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/23 18:51:48 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdint.h>
# include <math.h>

void	print_usage();
void	print_usage_commands();
int	command_md5(int ac, char **av);
int	command_sha256(int ac, char **av);

#endif
