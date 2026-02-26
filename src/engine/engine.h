/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:35:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/25 09:54:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "gfx/gfx.h"
# include "world/world.h"
# include "physics/physics.h"
# include "renderer/renderer.h"

typedef struct s_engine {
	t_options		opt;
	t_gfx			gfx;
	t_world_buffer	world_buffer;
	t_physics		physics;
	t_renderer		renderer;
}	t_engine;

int		engine_init(t_engine *e);
void	engine_deinit(t_engine *e);

#endif
