/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 09:57:46 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/27 10:25:55 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils/vectors.h"
#include "world/world.h"
#include "world/entity.h"
#include "hooks/hooks.h"

#include "physics_internal.h"

static t_entity	*find_door_at(t_world *w, int32_t tx, int32_t ty)
{
	uint32_t	i;
	t_entity	*e;

	i = 0;
	while (i < w->entity_count)
	{
		e = &w->entities[i];
		if (e->type == ENTITY_DOOR
			&& (int32_t)e->pos.x == tx
			&& (int32_t)e->pos.y == ty)
			return (e);
		i++;
	}
	return (NULL);
}

static void	animate_door(t_door *door)
{
	if (door->state == DOOR_OPENING)
	{
		door->offset += DOOR_SPEED;
		if (door->offset >= 1.0f)
		{
			door->offset = 1.0f;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->offset -= DOOR_SPEED;
		if (door->offset <= 0.0f)
		{
			door->offset = 0.0f;
			door->state = DOOR_CLOSED;
		}
	}
}

float	door_offset_at(const t_world *w, int32_t tx, int32_t ty)
{
	uint32_t	i;

	i = 0;
	while (i < w->entity_count)
	{
		if (w->entities[i].type == ENTITY_DOOR
			&& (int32_t)w->entities[i].pos.x == tx
			&& (int32_t)w->entities[i].pos.y == ty)
			return (w->entities[i].door.offset);
		i++;
	}
	return (0.0f);
}

void	toggle_door(t_world *world)
{
	t_vec2f		target;
	t_entity	*door;

	target.x = floorf(world->player.pos.x
			+ cosf(world->player.yaw) * INTERACT_DIST);
	target.y = floorf(world->player.pos.y
			+ sinf(world->player.yaw) * INTERACT_DIST);
	door = find_door_at(world, (int32_t)target.x, (int32_t)target.y);
	if (!door)
		return ;
	if (door->door.state == DOOR_CLOSED
		|| door->door.state == DOOR_CLOSING)
		door->door.state = DOOR_OPENING;
	else
		door->door.state = DOOR_CLOSING;
}

void	door_update(t_world *world, size_t i, t_input *input, float dt)
{
	(void)input;
	(void)dt;
	animate_door(&world->entities[i].door);
}
