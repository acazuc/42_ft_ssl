/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:17:33 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/13 21:52:42 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "bignum.h"

static t_program	g_programs[] = {{"help", command_help}
	, {"md4", command_md4}
	, {"md5", command_md5}
	, {"sha1", command_sha1}
	, {"sha224", command_sha224}
	, {"sha256", command_sha256}
	, {"sha384", command_sha384}
	, {"sha512", command_sha512}
	, {"base64", command_base64}
	, {"des", command_des1_cbc}
	, {"des-ecb", command_des1_ecb}
	, {"des-cbc", command_des1_cbc}
	, {"des-pcbc", command_des1_pcbc}
	, {"des-cfb", command_des1_cfb}
	, {"des-ofb", command_des1_ofb}
	, {"des-ctr", command_des1_ctr}
	, {"des-ede", command_des2_cbc}
	, {"des-ede-ecb", command_des2_ecb}
	, {"des-ede-cbc", command_des2_cbc}
	, {"des-ede-pcbc", command_des2_pcbc}
	, {"des-ede-cfb", command_des2_cfb}
	, {"des-ede-ofb", command_des2_ofb}
	, {"des-ede-ctr", command_des2_ctr}
	, {"des3", command_des3_cbc}
	, {"des-ede3", command_des3_cbc}
	, {"des-ede3-ecb", command_des3_ecb}
	, {"des-ede3-cbc", command_des3_cbc}
	, {"des-ede3-pcbc", command_des3_pcbc}
	, {"des-ede3-cfb", command_des3_cfb}
	, {"des-ede3-ofb", command_des3_ofb}
	, {"des-ede3-ctr", command_des3_ctr}
	, {"aes-128", command_aes_128_cbc}
	, {"aes-128-ecb", command_aes_128_ecb}
	, {"aes-128-cbc", command_aes_128_cbc}
	, {"aes-128-pcbc", command_aes_128_pcbc}
	, {"aes-128-cfb", command_aes_128_cfb}
	, {"aes-128-ofb", command_aes_128_ofb}
	, {"aes-128-ctr", command_aes_128_ctr}
	, {"aes-192", command_aes_192_cbc}
	, {"aes-192-ecb", command_aes_192_ecb}
	, {"aes-192-cbc", command_aes_192_cbc}
	, {"aes-192-pcbc", command_aes_192_pcbc}
	, {"aes-192-cfb", command_aes_192_cfb}
	, {"aes-192-ofb", command_aes_192_ofb}
	, {"aes-192-ctr", command_aes_192_ctr}
	, {"aes-256", command_aes_256_cbc}
	, {"aes-256-ecb", command_aes_256_ecb}
	, {"aes-256-cbc", command_aes_256_cbc}
	, {"aes-256-pcbc", command_aes_256_pcbc}
	, {"aes-256-cfb", command_aes_256_cfb}
	, {"aes-256-ofb", command_aes_256_ofb}
	, {"aes-256-ctr", command_aes_256_ctr}
	, {"camellia-128", command_camellia_128_cbc}
	, {"camellia-128-ecb", command_camellia_128_ecb}
	, {"camellia-128-cbc", command_camellia_128_cbc}
	, {"camellia-128-pcbc", command_camellia_128_pcbc}
	, {"camellia-128-cfb", command_camellia_128_cfb}
	, {"camellia-128-ofb", command_camellia_128_ofb}
	, {"camellia-128-ctr", command_camellia_128_ctr}
	, {"camellia-192", command_camellia_192_cbc}
	, {"camellia-192-ecb", command_camellia_192_ecb}
	, {"camellia-192-cbc", command_camellia_192_cbc}
	, {"camellia-192-pcbc", command_camellia_192_pcbc}
	, {"camellia-192-cfb", command_camellia_192_cfb}
	, {"camellia-192-ofb", command_camellia_192_ofb}
	, {"camellia-192-ctr", command_camellia_192_ctr}
	, {"camellia-256", command_camellia_256_cbc}
	, {"camellia-256-ecb", command_camellia_256_ecb}
	, {"camellia-256-cbc", command_camellia_256_cbc}
	, {"camellia-256-pcbc", command_camellia_256_pcbc}
	, {"camellia-256-cfb", command_camellia_256_cfb}
	, {"camellia-256-ofb", command_camellia_256_ofb}
	, {"camellia-256-ctr", command_camellia_256_ctr}
	, {"chacha20", command_chacha20}
	, {"rc4", command_rc4}
	, {"bignum", command_bignum}
	, {"genrsa", command_genrsa}
	, {"rsa", command_rsa}
	, {"rsautl", command_rsautl}};

int		main(int ac, char **av)
{
	uint32_t	i;

	if (ac < 2)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < sizeof(g_programs) / sizeof(*g_programs))
	{
		if (!ft_strcmp(av[1], g_programs[i].name))
			return (g_programs[i].fn(ac - 2, av + 2));
		++i;
	}
	ft_putstr("ft_ssl: invalid command: ");
	ft_putendl(av[1]);
	print_usage_commands();
	return (EXIT_FAILURE);
}
