/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/17 20:12:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>

void	print_ceiling(t_ray *ray, t_game *game, uint32_t x)
{
	uint32_t	color;
	uint32_t	y;

	color = game->data->ceiling_color;
	y = 0U;
	while (y < (uint32_t)ray->start)
	{
		if (y >= HEIGHT)
			break ;
		game->addr[y * WIDTH + x] = color;
		y++;
	}
}

void	print_floor(t_ray *ray, t_game *game, uint32_t x)
{
	uint32_t	color;
	uint32_t	y;

	color = game->data->floor_color;
	y = ray->end + 1;
	while (y < HEIGHT)
	{
		game->addr[y * WIDTH + x] = color;
		y++;
	}
}

void	print_texture(t_ray *ray, t_game *game, uint32_t x)
{
	t_texture	*tex;
	uint32_t	y;
	double		step;
	double		tex_pos;
	uint32_t	color;

	y = ray->start;
	tex = get_texture(ray, game);
	step = (float)tex->height / (float)ray->line_height;
	tex_pos = (ray->start - (float)HEIGHT / 2
			+ (float)ray->line_height / 2) * step;
	tex->x = find_intersection(ray, game->player) * tex->width;
	while (y <= (uint32_t)ray->end)
	{
		if (y >= HEIGHT)
			break ;
		tex->y = check_pos(tex_pos, tex);
		color = get_color(tex);
		game->addr[y * WIDTH + x] = color;
		tex_pos += step;
		y++;
	}
}

void	print_ray(t_ray *ray, t_game *game, int x)
{
	if (x < 0 || x >= WIDTH)
		return ;
	print_ceiling(ray, game, x);
	print_floor(ray, game, x);
	print_texture(ray, game, x);
}
