/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:24:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 13:29:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "common.h"
# include <stdatomic.h>

// temp
typedef struct s_v2f {
	float	x;
	float	y;
}	t_v2f;

typedef struct s_player
{
	t_v2f	pos;
	float	yaw;
	float	fov;
}	t_player;

typedef struct __attribute__((aligned(8))) s_world {
	t_player	player;
}	t_world;

typedef struct s_world_buffer {
	t_world		worlds[WORLD_COUNT];
	atomic_int	ready_index;
	char		reserved[4];
}	t_world_buffer;

int		world_buffer_init(t_world_buffer *wb);
void	world_buffer_deinit(t_world_buffer *wb);

#endif
