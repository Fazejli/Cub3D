/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:24:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/21 11:13:15 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "common.h"
# include "assets/assets.h"
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

int				world_buffer_init(t_world_buffer *wb, t_assets *a);
void			world_buffer_deinit(t_world_buffer *wb);

const t_world	*world_get_ready_snapshot(const t_world_buffer *wb);
t_world			*world_get_write_snapshot(t_world_buffer *wb);
void			world_publish_snapshot(t_world_buffer *wb);

#endif
