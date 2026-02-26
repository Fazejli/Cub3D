/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:31:29 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 07:06:15 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "physics/physics.h"
#include "renderer/renderer.h"

int	engine_init(t_engine *e)
{
	e->physics.world_buffer = &e->world_buffer;
	e->renderer.world_buffer = &e->world_buffer;
	e->renderer.gfx = &e->gfx;
	if (gfx_init(&e->gfx, &e->opt)
		|| world_buffer_init(&e->world_buffer)
		|| physics_init(&e->physics)
		|| renderer_init(&e->renderer, &e->opt))
	{
		engine_deinit(e);
		return (1);
	}
	return (0);
}
