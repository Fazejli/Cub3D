/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/24 12:05:19 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "assets/assets.h"
#include "utils/error.h"

#include "world.h"
#include <stddef.h>

static void	set_player(t_world *world, const t_map *map)
{
	world->player.pos.x = (float)(map->player_pos % map->width) + 0.5f;
	world->player.pos.y = (float)(map->player_pos / map->width) + 0.5f;
	world->player.vel.x = 0.0f;
	world->player.vel.y = 0.0f;
	world->player.yaw = (map->data[map->player_pos] == 'N') * 270.0f
		+ (map->data[map->player_pos] == 'S') * 90.0f
		+ (map->data[map->player_pos] == 'E') * 0.0f
		+ (map->data[map->player_pos] == 'W') * 180.0f;
	world->player.yaw_vel = 0.0f;
	world->player.fov = 90.0f;
}

static int	set_entities(t_world *world, const t_map *map, const t_tile *tiles)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (tiles[map->data[y * map->width + x]].flags & TILE_F_ENTITY)
			{
				if (world->entity_count >= MAX_ENTITIES)
					return (print_error(MOD_WORLD, ERR_ENTITY_LIMIT, 1));
				world->entities[world->entity_count].type = ENTITY_DOOR;
				world->entities[world->entity_count].pos.x = (float)x + 0.5f;
				world->entities[world->entity_count].pos.y = (float)y + 0.5f;
				world->entities[world->entity_count].door.state = DOOR_CLOSED;
				world->entities[world->entity_count].door.offset = 0.0f;
				world->entity_count++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	world_buffer_init(t_world_buffer *wb, t_assets *a)
{
	size_t	i;

	if (!wb || !a)
		return (print_error(MOD_WORLD, ERR_NULL_PTR, 1));
	set_player(&wb->worlds[0], &a->map);
	if (set_entities(&wb->worlds[0], &a->map, a->tiles))
		return (1);
	i = 1;
	while (i < WORLD_COUNT)
		memcpy(&wb->worlds[i++], &wb->worlds[0], sizeof(t_world));
	atomic_store(&wb->ready_index, 0);
	wb->write_index = 1;
	return (0);
}
