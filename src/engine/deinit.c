/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:45:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 17:13:52 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "assets/assets.h"
#include "gfx/gfx.h"
#include "physics/physics.h"
#include "world/world.h"
#include "physics/physics.h"

#include "engine.h"

#include <stdio.h>

void	engine_deinit(t_engine *e)
{
	gfx_deinit(&e->gfx);
	assets_deinit(&e->assets);
	world_buffer_deinit(&e->world_buffer);
	physics_deinit(&e->physics);
	memset(e, 0, sizeof(t_engine));
}
