/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 19:44:56 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (&game->textures[3]);
		else
			return (&game->textures[2]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->textures[1]);
		else
			return (&game->textures[0]);
	}
}

int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (mess_error("Failed to load texture"));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->size_len, &tex->endian);
	return (0);
}

static void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = HEIGHT / ray->dist;
	ray->start = (HEIGHT - ray->line_height) / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->start + ray->line_height;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT - 1;
}

void	calculate_distances(t_ray *ray)
{
	if (ray->side == 0)
		ray->dist = ray->dda.side_x - ray->dda.delta_x;
	else
		ray->dist = ray->dda.side_y - ray->dda.delta_y;
	calculate_wall_height(ray);
}
