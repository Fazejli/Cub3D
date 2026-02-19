/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/19 13:34:40 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "gfx.h"
#include "game.h"

#include "math_utils.h"

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

static int	gfx_load_textures(t_gfx *gfx, t_data *data)
{
	if (load_texture(game, &game->textures[NORTH], data->t_north)
		|| load_texture(game, &game->textures[SOUTH], data->t_south)
		|| load_texture(game, &game->textures[WEST], data->t_west)
		|| load_texture(game, &game->textures[EAST], data->t_east))
		return (free_data(data), 1);
	return (0);
}

static int	gfx_init_stage_two(t_gfx *gfx, t_options opt)
{
	gfx->frame.ptr = mlx_new_image(gfx->mlx, (int)opt.width, (int)opt.height);
	if (!gfx->frame.ptr)
	{
		// todo: print error
		return (1);
	}
	gfx->frame.data = (uint32_t *)(void *)mlx_get_data_addr(gfx->frame.ptr,
			(int *)&gfx->frame.bpp, (int *)&gfx->frame.linesz, &(int){0});
	gfx->frame.width = opt.width;
	gfx->frame.height = opt.height;
	// todo init font
	return (gfx_load_textures(gfx, opt));
}

int	gfx_init(t_gfx *gfx, t_options opt)
{
	ft_memset(&gfx, 0, sizeof(t_gfx));
	gfx->mlx = mlx_init();
	if (!gfx->mlx)
	{
		// todo: print error
		return (1);
	}
	gfx->win = mlx_new_window(gfx->mlx, (int)opt.width, (int)opt.height,
			(char *)(intptr_t)"Cub3D");
	if (!gfx->win)
	{
		// todo: print error
		return (1);
	}
	return (gfx_init_stage_two(gfx, opt));
}

int	init_game(t_game *game, t_data *data)
{
	ft_memset(game, 0, sizeof(t_game));
	game->data = data;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_data(data), 1);
	if (load_textures(game, data))
		return (1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT,
			(char *)(intptr_t)"Cub3D");
	if (!game->win)
		return (free_data(data), 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (free_data(data), 1);
	game->addr = (uint32_t *)(void *)mlx_get_data_addr(game->img, &game->bpp,
			&game->size_len, &game->endian);
	if (!game->addr)
		return (free_data(data), 1);
	init_player(&game->player, &data->player_pos);
	raycast(game);
	return (0);
}
