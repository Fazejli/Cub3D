/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:32:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/18 19:50:46 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mlx.h"
#include "hooks.h"

static int	game_destroy_hook(t_game *game)
{
	game_destroy(game, 0);
}

int	hooks_init(t_game *game)
{
	if (!game->gfx.win)
		return (1);
	mlx_hook(game->gfx.win, g_destroy_notify, 0,
		(t_hook_fn)(intptr_t)game_destroy_hook, game);
	hooks_keys_init(game);
	#if defined(__linux__)
		mlx_mouse_hide(game->gfx.mlx, game->gfx.win);
	#elif defined(__APPLE__)
		mlx_mouse_hide();
	#endif
	hooks_mouse_init(game);
	return (0);
}
