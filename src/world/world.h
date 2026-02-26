/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:24:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/26 13:08:16 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "common.h"
# include "world/entity.h"
# include <stdatomic.h>

typedef struct __attribute__((aligned(8))) s_world {
	t_player	player;
	t_entity	entities[MAX_ENTITIES];
	int			entity_count;
	char		reserved[4];
}	t_world;

typedef struct s_world_buffer {
	t_world		worlds[WORLD_COUNT];
	atomic_int	ready_index;
	int			write_index;
}	t_world_buffer;

int				world_buffer_init(t_world_buffer *wb);
void			world_buffer_deinit(t_world_buffer *wb);

const t_world	*world_get_ready_snapshot(const t_world_buffer *wb);
t_world			*world_get_write_snapshot(t_world_buffer *wb);
void			world_publish_snapshot(t_world_buffer *wb);

#endif
