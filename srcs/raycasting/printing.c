/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 19:55:35 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_ceiling(t_ray *ray, t_game *game, int col)
{
	int	color;
	int	pixel;

	color = game->data->ceiling_color;
	pixel = 0;
	while (pixel < ray->start)
	{
		mlx_pixel_put(game->mlx, game->win, col, pixel, color);
		pixel++;
	}
}

void	print_floor(t_ray *ray, t_game *game, int col)
{
	int	color;
	int	pixel;

	color = game->data->floor_color;
	pixel = ray->end + 1;
	while (pixel < HEIGHT)
	{
		mlx_pixel_put(game->mlx, game->win, col, pixel, color);
		pixel++;
	}
}

void	print_texture(t_ray *ray, t_game *game, int col)
{
	int	i;

	i = ray->start;
	while (i <= ray->end)
	{
		mlx_pixel_put(game->mlx, game->win, col, i, 0xFFFFFF1);
		i++;
	}
}

void	print_ray(t_ray *ray, t_game *game, int col)
{
	print_ceiling(ray, game, col);
	print_floor(ray, game, col);
	print_texture(ray, game, col);
}
