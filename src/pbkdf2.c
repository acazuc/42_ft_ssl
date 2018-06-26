/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:54:15 by acazuc            #+#    #+#             */
/*   Updated: 2018/06/26 22:06:44 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*typedef struct	s_hmac_ctx
{
	t_hash_init	*hash_init;
	t_hash_update	*hash_update;
	t_hash_final	*hash_final;
	void		*hash_ctx;
	uint8_t		block_size;
	uint8_t		hash_size;
	uint8_t		*key;
	uint32_t	key_len;
	uint8_t		*msg;
	uint32_t	msg_len;
}		t_hmac_ctx;*/

/*typedef struct	s_pbkdf2_ctx
{
	char		*password;
	size_t		password_len;
	char		*salt;
	size_t		salt_len;
	uint32_t	iterations;
	void		*out;
	size_t		out_len;
	t_hash_init	*hash_init;
	t_hash_update	*hash_update;
	t_hash_final	*hash_final;
	void		*hash_ctx;
	uint8_t		hash_size;

}		t_pbkdf2_ctx;*/

static int	loop(t_pbkdf2_ctx *ctx, int i, char *tmp, char *hash)
{
	uint32_t	salt_tmp;
	//char		*hash_tmp;
	uint32_t	j;

	ft_memcpy(tmp, ctx->salt, ctx->salt_len);
	salt_tmp = ft_swap_uint(i);
	ft_memcpy(tmp + ctx->salt_len, &salt_tmp, 4);
	j = 0;
	while (j < ctx->iterations)
	{
		//
		++j;
	}
	(void)hash;
	return (1);
}

char		*pbkdf2(t_pbkdf2_ctx *ctx)
{
	uint32_t	blocks;
	uint32_t	i;
	char		*tmp;
	char		*hash;

	if (!(tmp = malloc(ctx->salt_len + 4)))
		return (NULL);
	if (!(hash = malloc(ctx->hmac->h.h->digest_len)))
	{
		free(tmp);
		return (NULL);
	}
	blocks = ctx->out_len / ctx->hmac->h.h->digest_len
		+ (ctx->out_len % ctx->hmac->h.h->digest_len > 0 ? 1 : 0);
	i = 0;
	while (++i <= blocks)
	{
		if (!loop(ctx, i, tmp, hash))
		{
			free(hash);
			free(tmp);
			return (NULL);
		}
	}
	return (NULL);
}
