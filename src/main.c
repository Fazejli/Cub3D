/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/27 16:15:26 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gfx/gfx.h"
#include "engine/engine.h"
#include "renderer/renderer.h"

static int	loop2(t_engine *e)
{
	renderer_render(&e->renderer);
	gfx_present(&e->gfx, renderer_get_ready_frame(&e->renderer));
	return (0);
}

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (engine_init(&engine, argc, argv))
		return (1);
	gfx_loop(&engine.gfx, (int (*)(void))(intptr_t)loop2, &engine);
	return (0);
}
