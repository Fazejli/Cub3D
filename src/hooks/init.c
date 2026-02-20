/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:32:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/20 11:30:05 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "mlx.h"
#include "hooks.h"

static int	game_destroy_hook(t_game *game)
{
	game_destroy(game, 0);
}

#if defined(__linux__)

int	hooks_init(t_game *game)
{
	game->gfx.win = game->win;
	game->gfx.mlx = game->mlx;
	// if (!game->win)
	// 	return (1);
	mlx_hook(game->gfx.win, evDestroyNotify, 0,
		(t_hook_fn)(intptr_t)game_destroy_hook, game);
	hooks_keys_init(game);
	mlx_mouse_hide(game->gfx.mlx, game->gfx.win);
	hooks_mouse_init(game);
	return (0);
}

#elif defined(__APPLE__)

int	hooks_init(t_game *game)
{
	if (!game->gfx.win)
		return (1);
	mlx_hook(game->gfx.win, evDestroyNotify, 0,
		(t_hook_fn)(intptr_t)game_destroy_hook, game);
	hooks_keys_init(game);
	mlx_mouse_hide();
	hooks_mouse_init(game);
	return (0);
}

#endif
