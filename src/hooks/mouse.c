/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:39:59 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/19 18:57:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"

static int	on_mouse_down(int button, int x, int y, t_game *game)
{
	// todo
	(void)button;
	(void)x;
	(void)y;
	(void)game;
	return (0);
}

int	hooks_mouse_init(t_game *game)
{
	mlx_hook(game->gfx.win, evButtonPress, evButtonPressMask,
		(t_hook_fn)(intptr_t)on_mouse_down, game);
	return (0);
}
