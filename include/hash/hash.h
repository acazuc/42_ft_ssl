/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:38:04 by acazuc            #+#    #+#             */
/*   Updated: 2018/08/15 19:51:29 by acazuc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include <stdint.h>
# include <stddef.h>

typedef int (*t_hash_init)(void *ctx);
typedef int (*t_hash_update)(void *ctx, const uint8_t *data, size_t len);
typedef int (*t_hash_final)(uint8_t *md, void *ctx);

typedef struct		s_hash
{
	t_hash_init	init;
	t_hash_update	update;
	t_hash_final	final;
	uint8_t		digest_len;
	uint8_t		block_len;
	uint8_t		ctx_len;
	char		*name;
}			t_hash;

typedef struct		s_hash_ctx
{
	t_hash		*hash;
	void		*ctx;
}			t_hash_ctx;

int	hash_init(t_hash_ctx *ctx, t_hash *hash);
int	hash_update(t_hash_ctx *ctx, uint8_t *data, size_t len);
int	hash_final(t_hash_ctx *ctx, uint8_t *md);

#endif
