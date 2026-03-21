/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:49:02 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/21 15:45:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdatomic.h>
#include <stdio.h>

#include "assets/assets.h"
#include "world/world.h"
#include "hooks/hooks.h"
#include "utils/utils.h"
#include "common.h"

#include "physics.h"

static void	print_steps_per_sec(void)
{
	static long	last_step_time = 0;
	static int	step_count = 0;
	long		now;
	double		steps_per_sec;

	step_count++;
	now = get_timestamp_us();
	if (last_step_time == 0)
		last_step_time = now;
	if (now - last_step_time >= 1000000L)
	{
		steps_per_sec = (double)step_count * 1000000.0
			/ (double)(now - last_step_time);
		dprintf(2, "Engine Steps/s: %.2f\n", steps_per_sec);
		step_count = 0;
		last_step_time = now;
	}
}

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
	world->player.yaw_vel
		+= MOUSE_SENSITIVITY
		* (float)((input->mouse.delta_x != 0) * input->mouse.delta_x);
	input->mouse.delta_x = 0;
	input->mouse.delta_z = 0;
}

static bool	is_solid(t_map *map, t_tile *tiles, float x, float y)
{
	if (x < 0.0f || x >= (float)map->width
		|| y < 0.0f || y >= (float)map->height)
		return (true);
	return ((tiles[map->data[(uint32_t)y * map->width + (uint32_t)x]].flags
			& TILE_F_WALKABLE) == 0);
}

static void	apply_collisions(t_world *world, t_map *map, t_tile *tiles)
{
	t_vec2f	next_pos;

	next_pos.x = world->player.pos.x + world->player.vel.x;
	next_pos.y = world->player.pos.y + world->player.vel.y;
	if (is_solid(map, tiles, next_pos.x - ENTITY_SIZE, world->player.pos.y)
		|| is_solid(map, tiles, next_pos.x + ENTITY_SIZE, world->player.pos.y))
		world->player.vel.x = 0.0f;
	if (is_solid(map, tiles, world->player.pos.x, next_pos.y - ENTITY_SIZE)
		|| is_solid(map, tiles, world->player.pos.x, next_pos.y + ENTITY_SIZE))
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

void	physics_update(t_physics *p, float dt)
{
	t_world			*world;

	if (!p || !p->world_buffer || !p->input)
		return ;
	world = world_get_write_snapshot(p->world_buffer);
	*world = *world_get_ready_snapshot(p->world_buffer);
	(void)dt;
	apply_input(world, p->input);
	apply_collisions(world, &p->assets->map, p->assets->tiles);
	apply_inertia(world);
	world_publish_snapshot(p->world_buffer);
	print_steps_per_sec();
}
