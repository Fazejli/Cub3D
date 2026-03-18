/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 16:51:36 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets/assets.h"

#include "world.h"
#include <stddef.h>

static void	set_player(t_world *world, size_t x, size_t y)
{
	world->player.pos.x = (float)x + 0.5f;
	world->player.pos.y = (float)y + 0.5f;
	world->player.yaw = 0.0f;
	world->player.fov = 90.0f;
}

int	world_buffer_init(t_world_buffer *wb, t_assets *a)
{
	size_t	player_x;
	size_t	player_y;
	size_t	i;

	if (!wb || !a)
		return (1);
	player_x = a->map.player_pos % a->map.width;
	player_y = a->map.player_pos / a->map.width;
	i = 0;
	while (i < WORLD_COUNT)
		set_player(&wb->worlds[i++], player_x, player_y);
	atomic_store(&wb->ready_index, 0);
	wb->write_index = 1;
	return (0);
}
