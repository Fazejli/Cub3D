/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:56:21 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 16:22:41 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

#include "assets/assets.h"
#include "world/world.h"
#include "hooks/hooks.h"

#include "physics/physics_internal.h"

static bool	solid(t_world *w, t_assets *a, float x, float y)
{
	uint32_t	idx;
	uint8_t		tile_id;

	if (x < 0.0f || x >= (float)a->map.width
		|| y < 0.0f || y >= (float)a->map.height)
		return (true);
	idx = (uint32_t)y * (uint32_t)a->map.width + (uint32_t)x;
	tile_id = a->map.data[idx];
	if (a->tiles[tile_id].flags & TILE_F_DOOR)
		return (door_offset_at(w, (int32_t)x, (int32_t)y) < 0.6f);
	return (a->tiles[tile_id].flags & TILE_F_SOLID);
}

static bool	is_next_pos_other_solid(t_assets *a, t_vec2f pos, t_vec2f next)
{
	uint8_t		next_tile_id;

	if (next.x < 0.0f || next.x >= (float)a->map.width
		|| next.y < 0.0f || next.y >= (float)a->map.height)
		return (true);
	if ((uint32_t)pos.x == (uint32_t)next.x
		&& (uint32_t)pos.y == (uint32_t)next.y)
		return (false);
	next_tile_id = a->map.data[(uint32_t)next.y
		* (uint32_t)a->map.width + (uint32_t)next.x];
	return (a->tiles[next_tile_id].flags & TILE_F_SOLID);
}

void	apply_collisions(t_world *w, t_assets *a)
{
	const t_vec2f	next = {{w->player.pos.x + w->player.vel.x,
		w->player.pos.y + w->player.vel.y}};

	if (solid(w, a, w->player.pos.x, w->player.pos.y))
	{
		if (is_next_pos_other_solid(a, w->player.pos, next))
			w->player.pos = (t_vec2f){{0.0f, 0.0f}};
		return ;
	}
	if ((solid(w, a, next.x - ENTITY_SIZE, w->player.pos.y - ENTITY_SIZE)
			|| solid(w, a, next.x - ENTITY_SIZE, w->player.pos.y + ENTITY_SIZE))
		&& w->player.vel.x < 0.0f)
			w->player.vel.x = 0.0f;
	if ((solid(w, a, next.x + ENTITY_SIZE, w->player.pos.y - ENTITY_SIZE)
			|| solid(w, a, next.x + ENTITY_SIZE, w->player.pos.y + ENTITY_SIZE))
		&& w->player.vel.x > 0.0f)
			w->player.vel.x = 0.0f;
	if ((solid(w, a, w->player.pos.x - ENTITY_SIZE, next.y - ENTITY_SIZE)
			|| solid(w, a, w->player.pos.x - ENTITY_SIZE, next.y + ENTITY_SIZE))
		&& w->player.vel.y < 0.0f)
			w->player.vel.y = 0.0f;
	if ((solid(w, a, w->player.pos.x + ENTITY_SIZE, next.y - ENTITY_SIZE)
			|| solid(w, a, w->player.pos.x + ENTITY_SIZE, next.y + ENTITY_SIZE))
		&& w->player.vel.y > 0.0f)
			w->player.vel.y = 0.0f;
}
