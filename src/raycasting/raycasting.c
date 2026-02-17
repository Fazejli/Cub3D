/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/17 19:09:26 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

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
		if (ray->pos_y < 0 || ray->pos_y >= get_height(map))
			wall = 1;
		else if (ray->pos_x < 0 || ray->pos_x >= (int)ft_strlen(map[ray->pos_y]))
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
		ray->dda.delta_x = fabs(1.0 / ray->dir.x);
		ray->dda.side_x = (player->pos.x - ray->pos_x) * ray->dda.delta_x;
	}
	else
	{
		ray->dda.step_x = 1;
		ray->dda.delta_x = fabs(1.0 / ray->dir.x);
		ray->dda.side_x = (ray->pos_x + 1.0 - player->pos.x) * ray->dda.delta_x;
	}
	if (ray->dir.y < 0)
	{
		ray->dda.step_y = -1;
		ray->dda.delta_y = fabs(1.0 / ray->dir.y);
		ray->dda.side_y = (player->pos.y - ray->pos_y) * ray->dda.delta_y;
	}
	else
	{
		ray->dda.step_y = 1;
		ray->dda.delta_y = fabs(1.0 / ray->dir.y);
		ray->dda.side_y = (ray->pos_y + 1.0 - player->pos.y) * ray->dda.delta_y;
	}
}

static void	init_ray(t_ray *ray, t_player *player, int x)
{
	const double	cam = 2.0 * x / (float)WIDTH - 1.0;
	const double	dir_x = cos(player->yaw);
	const double	dir_y = sin(player->yaw);
	const double	plane = tan(player->fov * 0.5);

	ray->dir.x = dir_x - dir_y * cam * plane;
	ray->dir.y = dir_y + dir_x * cam * plane;
	ray->pos_x = (int)player->pos.x;
	ray->pos_y = (int)player->pos.y;
	init_dda(ray, player);
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

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
