/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:50:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/18 14:48:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"
#include <stdint.h>

enum e_key_bits : uint8_t {
	KEY_FORWARD,
	KEY_BACKWARD,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_YAW_LEFT,
	KEY_YAW_RIGHT,
	KEY_PITCH_UP,
	KEY_PITCH_DOWN,
	KEY_COUNT
};

static const int	g_keymap[KEY_COUNT] = {
[KEY_FORWARD] = g_key_w,
[KEY_BACKWARD] = g_key_s,
[KEY_LEFT] = g_key_a,
[KEY_RIGHT] = g_key_d,
[KEY_UP] = g_key_space,
[KEY_DOWN] = g_key_c,
[KEY_YAW_LEFT] = g_key_left,
[KEY_YAW_RIGHT] = g_key_right,
[KEY_PITCH_UP] = g_key_up,
[KEY_PITCH_DOWN] = g_key_down,
};

static inline void	key_update(uint32_t *bits, int keysym, uint32_t pressed)
{
	uint32_t	mask;
	uint32_t	match;
	uint8_t		i;

	i = 0;
	mask = 0;
	while (i < KEY_COUNT)
	{
		match = (keysym == g_keymap[i]);
		mask |= match << i;
		i++;
	}
	*bits ^= (-pressed ^ *bits) & mask;
}

static int	key_press_hook(int keysym, t_game *game)
{
	key_update(&game->input.keys.bits, keysym, 1);
	return (0);
}

static int	key_release_hook(int keysym, t_game *game)
{
	key_update(&game->input.keys.bits, keysym, 0);
	return (0);
}

int	hooks_keys_init(t_game *game)
{
	mlx_hook(game->gfx.win, g_key_press, g_key_press_mask,
		(t_hook_fn)(intptr_t)key_press_hook, game);
	mlx_hook(game->gfx.win, g_key_release, g_key_release_mask,
		(t_hook_fn)(intptr_t)key_release_hook, game);
	return (0);
}

