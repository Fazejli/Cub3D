/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:19:42 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "mlx.h"

int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			(int *)&tex->width, (int *)&tex->height);
	if (!tex->img)
		return (mess_error("Failed to load texture"));
	tex->addr = (uint32_t *)(void *)mlx_get_data_addr(tex->img,
			(int *)&tex->bpp, (int *)&tex->size_len, (int *)&tex->endian);
	return (0);
}

static void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (uint32_t)(HEIGHT / ray->dist);
	if (ray->line_height >= HEIGHT)
	{
		ray->start = 0;
		ray->end = HEIGHT - 1;
		return ;
	}
	ray->start = (HEIGHT - ray->line_height) / 2;
	ray->end = ray->start + ray->line_height;
}

void	calculate_distances(t_ray *ray)
{
	if (ray->side == WEST || ray->side == EAST)
		ray->dist = ray->dda.side_x - ray->dda.delta_x;
	else
		ray->dist = ray->dda.side_y - ray->dda.delta_y;
	if (ray->dist <= 0)
		ray->dist = 0.0001f;
	calculate_wall_height(ray);
}
