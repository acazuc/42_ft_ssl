/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/23 21:19:16 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdint.h>
# include <math.h>

void		print_usage();
void		print_usage_commands();
int		command_md5(int ac, char **av);
int		command_sha256(int ac, char **av);
uint32_t	rotate_left(uint32_t v, uint32_t c);
uint32_t	rotate_right(uint32_t v, uint32_t c);

#endif
