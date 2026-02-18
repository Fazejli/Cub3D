/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 16:12:46 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mlx.h"
#include <stdint.h>

static void	print_ceiling(t_ray *ray, t_game *game, uint32_t x)
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

static void	print_floor(t_ray *ray, t_game *game, uint32_t x)
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

static void	print_texture(t_ray *ray, t_game *game, uint32_t x)
{
	t_texture	*tex;
	uint32_t	y;
	uint32_t	tx;
	float		step;
	float		tex_pos;

	y = ray->start;
	tex = get_texture(ray, game);
	step = (float)tex->height / (float)ray->line_height;
	tex_pos = ((float)ray->start - (float)HEIGHT / 2
			+ (float)ray->line_height / 2) * step;
	tx = (uint32_t)(find_intersection(ray, game->player) * (float)tex->width);
	while (y <= (uint32_t)ray->end)
	{
		if (y >= HEIGHT)
			break ;
		game->addr[y * WIDTH + x] = get_color(tex, tx, check_pos(tex_pos, tex));
		tex_pos += step;
		y++;
	}
}

void	print_ray(t_ray *ray, t_game *game, uint32_t x)
{
	if (x >= WIDTH)
		return ;
	print_ceiling(ray, game, x);
	print_floor(ray, game, x);
	print_texture(ray, game, x);
}
