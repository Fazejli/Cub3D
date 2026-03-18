/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:49:02 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 17:39:03 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdatomic.h>
#include <stdio.h>

#include "world/world.h"
#include "hooks/hooks.h"
#include "utils/utils.h"

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
	if (input->keys.values.forward)
		world->player.pos.y += MOVE_SPEED * (1.0f / 128.0f);
	if (input->keys.values.backward)
		world->player.pos.y -= MOVE_SPEED * (1.0f / 128.0f);
	if (input->keys.values.left)
		world->player.pos.x -= MOVE_SPEED * (1.0f / 128.0f);
	if (input->keys.values.right)
		world->player.pos.x += MOVE_SPEED * (1.0f / 128.0f);
	if (input->keys.values.yaw_left)
		world->player.yaw -= ROT_SPEED * (1.0f / 128.0f);
	if (input->keys.values.yaw_right)
		world->player.yaw += ROT_SPEED * (1.0f / 128.0f);
	if (input->mouse.delta_x != 0)
		world->player.yaw += input->mouse.delta_x * MOUSE_SENSITIVITY;
	input->mouse.delta_x = 0;
	input->mouse.delta_y = 0;
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
	world_publish_snapshot(p->world_buffer);
	print_steps_per_sec();
}
