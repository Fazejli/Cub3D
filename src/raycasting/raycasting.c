/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:14:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "game.h"
#include "mlx.h"
#include <math.h>
#include <stdint.h>

static void	find_wall(t_ray *ray, char **map)
{
	int	wall;

	wall = 0;
	while (!wall)
	{
		if (ray->dda.side_x < ray->dda.side_y)
		{
			ray->dda.side_x += ray->dda.delta_x;
			ray->pos_x += ray->dda.step_x;
			ray->side = EAST;
		}
		else
		{
			ray->dda.side_y += ray->dda.delta_y;
			ray->pos_y += ray->dda.step_y;
			ray->side = NORTH;
		}
		if (ray->pos_y < 0 || (uint32_t)ray->pos_y >= get_height(map))
			wall = 1;
		else if (ray->pos_x < 0
			|| (uint32_t)ray->pos_x >= ft_strlen(map[ray->pos_y]))
			wall = 1;
		else if (!wall && map[ray->pos_y][ray->pos_x] == '1')
			wall = 1;
	}
	calculate_distances(ray);
}

static void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->dda.step_x = -1;
		ray->dda.delta_x = fabsf(1.0f / ray->dir.x);
		ray->dda.side_x = (player->pos.x - (float)ray->pos_x) * ray->dda.delta_x;
	}
	else
	{
		ray->dda.step_x = 1;
		ray->dda.delta_x = fabsf(1.0f / ray->dir.x);
		ray->dda.side_x = ((float)ray->pos_x + 1.0f - player->pos.x) * ray->dda.delta_x;
	}
	if (ray->dir.y < 0)
	{
		ray->dda.step_y = -1;
		ray->dda.delta_y = fabsf(1.0f / ray->dir.y);
		ray->dda.side_y = (player->pos.y - (float)ray->pos_y) * ray->dda.delta_y;
	}
	else
	{
		ray->dda.step_y = 1;
		ray->dda.delta_y = fabsf(1.0f / ray->dir.y);
		ray->dda.side_y = ((float)ray->pos_y + 1.0f - player->pos.y) * ray->dda.delta_y;
	}
}

static void	init_ray(t_ray *ray, t_player *player, uint32_t x)
{
	const float	cam = 2.0f * (float)x / (float)WIDTH - 1.0f;
	const float	dir_x = cosf(player->yaw);
	const float	dir_y = sinf(player->yaw);
	const float	plane = tanf(player->fov * 0.5f);

	ray->dir.x = dir_x - dir_y * cam * plane;
	ray->dir.y = dir_y + dir_x * cam * plane;
	ray->pos_x = (int)player->pos.x;
	ray->pos_y = (int)player->pos.y;
	init_dda(ray, player);
}

void	raycast(t_game *game)
{
	t_ray		ray;
	uint32_t	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &game->player, x);
		find_wall(&ray, game->data->map);
		print_ray(&ray, game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
