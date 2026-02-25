/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:49:02 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 05:25:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "physics.h"
#include "world/world.h"
#include "utils/utils.h"
#include <stdatomic.h>
#include <stdio.h>

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

void	physics_update(t_physics *p, float dt)
{
	t_world			*world;

	world = world_get_write_snapshot(p->world_buffer);
	*world = *world_get_ready_snapshot(p->world_buffer);
	(void)dt;
	// apply_input(write_world);
	// physics_step(write_world, dt);
	world_publish_snapshot(p->world_buffer);
	print_steps_per_sec();
}
