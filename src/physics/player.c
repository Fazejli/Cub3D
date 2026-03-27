/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:46:27 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/27 16:13:29 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "assets/assets.h"
#include "world/world.h"
#include "hooks/hooks.h"
#include "common.h"

#include "physics/physics_internal.h"

static void	apply_keys_input(t_world *world, t_input *input)
{
	t_player	*p;
	t_keys		k;
	t_vec2f		d;
	float		len;

	p = &world->player;
	k = input->keys;
	d.x = (k.values.forward != 0) * cosf(p->yaw)
		- (k.values.backward != 0) * cosf(p->yaw)
		+ (k.values.left != 0) * sinf(p->yaw)
		- (k.values.right != 0) * sinf(p->yaw);
	d.y = (k.values.forward != 0) * sinf(p->yaw)
		- (k.values.backward != 0) * sinf(p->yaw)
		- (k.values.left != 0) * cosf(p->yaw)
		+ (k.values.right != 0) * cosf(p->yaw);
	len = sqrtf(d.x * d.x + d.y * d.y);
	if (len > 0.0f)
	{
		p->vel.x += (d.x / len) * MOVE_SPEED;
		p->vel.y += (d.y / len) * MOVE_SPEED;
	}
	p->yaw_vel -= (k.values.yaw_left != 0) * ROT_SPEED;
	p->yaw_vel += (k.values.yaw_right != 0) * ROT_SPEED;
	p->fov = fmaxf(FOV_MIN, p->fov + (k.values.zoom_in != 0) * ZOOM_SPEED);
	p->fov = fminf(FOV_MAX, p->fov - (k.values.zoom_out != 0) * ZOOM_SPEED);
}

static void	apply_mouse_input(t_world *world, t_input *input)
{
	world->player.yaw_vel += MOUSE_SENSITIVITY
		* (float)((input->mouse.delta_x != 0) * input->mouse.delta_x);
	input->mouse.delta_x = 0;
	input->mouse.delta_z = 0;
}

static void	apply_friction(t_world *world)
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
	apply_keys_input(world, input);
	apply_mouse_input(world, input);
	apply_collisions(world, a);
	apply_friction(world);
}
