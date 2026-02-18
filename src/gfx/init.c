/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 11:42:33 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"

#include "math_utils.h"

__attribute__((always_inline))
static inline void	vector_init(t_vector *v, float x, float y)
{
	v->x = x;
	v->y = y;
}

static void	player_init(t_player *player, t_pos *pos)
{
	constexpr const float	orientations[]
		= {0, 3 * PI_2, PI, PI_2};

	player->pos.x = pos->x + 0.5f;
	player->pos.y = pos->y + 0.5f;
	// todo add FOV parameter
	player->fov = 90.0f * PI / 180.0f;
	player->yaw = orientations[pos->dir];
}

static int	load_textures(t_game *game, t_data *data)
{
	if (load_texture(game, &game->textures[NORTH], data->t_north)
		|| load_texture(game, &game->textures[SOUTH], data->t_south)
		|| load_texture(game, &game->textures[WEST], data->t_west)
		|| load_texture(game, &game->textures[EAST], data->t_east))
		return (free_data(data), 1);
	return (0);
}

typedef int	(*t_fn)();

int	init_game(t_game *game, t_data *data)
{
	memset(game, 0, sizeof(t_game));
	game->data = data;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_data(data), 1);
	if (load_textures(game, data))
		return (1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		return (free_data(data), 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (free_data(data), 1);
	game->addr = (uint32_t *)mlx_get_data_addr(game->img, &game->bpp,
			&game->size_len, &game->endian);
	if (!game->addr)
		return (free_data(data), 1);
	init_player(&game->player, &data->player_pos);
	raycast(game);
	mlx_hook(game->win, ON_DESTROY, 0, (t_fn)(intptr_t)quit_game, game);
	mlx_key_hook(game->win, (t_fn)(intptr_t)key_press, game);
	return (0);
}
