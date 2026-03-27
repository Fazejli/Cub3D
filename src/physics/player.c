/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:46:27 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/24 12:24:20 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "assets/assets.h"
#include "world/world.h"
#include "hooks/hooks.h"
#include "common.h"

#include "physics/physics_internal.h"

static void	apply_input(t_world *world, t_input *input)
{
	t_vec2f	d;
	float	len;

	d.x = (input->keys.values.forward != 0) * cosf(world->player.yaw)
		- (input->keys.values.backward != 0) * cosf(world->player.yaw)
		+ (input->keys.values.left != 0) * sinf(world->player.yaw)
		- (input->keys.values.right != 0) * sinf(world->player.yaw);
	d.y = (input->keys.values.forward != 0) * sinf(world->player.yaw)
		- (input->keys.values.backward != 0) * sinf(world->player.yaw)
		- (input->keys.values.left != 0) * cosf(world->player.yaw)
		+ (input->keys.values.right != 0) * cosf(world->player.yaw);
	len = sqrtf(d.x * d.x + d.y * d.y);
	if (len > 0.0f)
	{
		world->player.vel.x += (d.x / len) * MOVE_SPEED;
		world->player.vel.y += (d.y / len) * MOVE_SPEED;
	}
	world->player.yaw_vel -= (input->keys.values.yaw_left != 0) * ROT_SPEED;
	world->player.yaw_vel += (input->keys.values.yaw_right != 0) * ROT_SPEED;
	world->player.yaw_vel += MOUSE_SENSITIVITY
		* (float)((input->mouse.delta_x != 0) * input->mouse.delta_x);
	input->mouse.delta_x = 0;
	input->mouse.delta_z = 0;
}

static bool	is_solid(t_world *w, t_assets *a, float x, float y)
{
	uint32_t	idx;
	uint8_t		tile_id;

	if (x < 0.0f || x >= (float)a->map.width
		|| y < 0.0f || y >= (float)a->map.height)
		return (true);
	idx = (uint32_t)y * (uint32_t)a->map.width + (uint32_t)x;
	tile_id = a->map.data[idx];
	if (a->tiles[tile_id].flags & TILE_F_DOOR)
		return (door_offset_at(w, (int32_t)x, (int32_t)y) < 0.9f);
	return (a->tiles[tile_id].flags & TILE_F_SOLID);
}

static void	apply_collisions(t_world *world, t_assets *a)
{
	t_vec2f	next_pos;

	next_pos.x = world->player.pos.x + world->player.vel.x;
	next_pos.y = world->player.pos.y + world->player.vel.y;
	if (is_solid(world, a,
			next_pos.x - ENTITY_SIZE, world->player.pos.y - ENTITY_SIZE)
		|| is_solid(world, a,
			next_pos.x - ENTITY_SIZE, world->player.pos.y + ENTITY_SIZE)
		|| is_solid(world, a,
			next_pos.x + ENTITY_SIZE, world->player.pos.y - ENTITY_SIZE)
		|| is_solid(world, a,
			next_pos.x + ENTITY_SIZE, world->player.pos.y + ENTITY_SIZE))
		world->player.vel.x = 0.0f;
	if (is_solid(world, a,
			world->player.pos.x - ENTITY_SIZE, next_pos.y - ENTITY_SIZE)
		|| is_solid(world, a,
			world->player.pos.x - ENTITY_SIZE, next_pos.y + ENTITY_SIZE)
		|| is_solid(world, a,
			world->player.pos.x + ENTITY_SIZE, next_pos.y - ENTITY_SIZE)
		|| is_solid(world, a,
			world->player.pos.x + ENTITY_SIZE, next_pos.y + ENTITY_SIZE))
		world->player.vel.y = 0.0f;
}

static void	apply_inertia(t_world *world)
{
	world->player.pos.x += world->player.vel.x;
	world->player.pos.y += world->player.vel.y;
	world->player.yaw += world->player.yaw_vel;
	world->player.vel.x *= FRICTION;
	world->player.vel.y *= FRICTION;
	world->player.yaw_vel *= FRICTION;
}

void	player_update(t_world *world, t_assets *a, t_input *input)
{
	apply_input(world, input);
	apply_collisions(world, a);
	apply_inertia(world);
}
