/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:30:33 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/24 14:10:18 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "utils/error.h"
#include "world/world.h"
#include "world/entity.h"

#include "physics_internal.h"

const t_entity_update_fn	g_entity_update_fns[] = {
[ENTITY_NONE] = NULL,
[ENTITY_DOOR] = door_update,
};

static void	entities_toggle(t_world *world, t_input *input)
{
	if (input->interact_pressed)
	{
		input->interact_pressed = false;
		toggle_door(world);
	}
}

void	entities_update(t_world *world, t_input *input, float dt)
{
	t_entity_type	type;
	size_t			i;

	entities_toggle(world, input);
	i = 0;
	while (i < world->entity_count)
	{
		type = world->entities[i].type;
		if (type > ENTITY_NONE && type < ENTITY_UNKNOWN)
			g_entity_update_fns[type](world, i, input, dt);
		if (type >= ENTITY_UNKNOWN)
			print_warning(MOD_PHYSICS, WARN_UNKNOWN_ENTITY, 1);
		i++;
	}
}
