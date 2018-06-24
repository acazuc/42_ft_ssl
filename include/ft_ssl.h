/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:29 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/24 11:55:12 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdint.h>
# include <math.h>

typedef struct	s_b64e_data
{
	int	fd;
	int	count;
}		t_b64e_data;

void		print_usage();
void		print_usage_commands();
int		command_md5(int ac, char **av);
int		command_sha1(int ac, char **av);
int		command_sha224(int ac, char **av);
int		command_sha256(int ac, char **av);
int		command_sha384(int ac, char **av);
int		command_sha512(int ac, char **av);
int		command_base64(int ac, char **av);
uint32_t	rotate_left(uint32_t v, uint32_t c);
uint64_t	rotate_left64(uint64_t v, uint64_t c);
uint32_t	rotate_right(uint32_t v, uint32_t c);
uint64_t	rotate_right64(uint64_t v, uint64_t c);

#endif
