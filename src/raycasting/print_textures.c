/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:17:03 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/18 16:10:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include <stdint.h>
#include <math.h>

uint32_t	get_color(t_texture *tex, uint32_t x, uint32_t y)
{
	uint32_t	offset;
	uint32_t	color;

	offset = y * (tex->size_len / (tex->bpp / 8)) + x;
	color = tex->addr[offset];
	return (color);
}

uint32_t	check_pos(float pos, t_texture *tex)
{
	if (pos < 0)
		return (0);
	else if (pos >= (float)tex->height)
		return (tex->height - 1);
	return ((uint32_t)pos);
}

float	find_intersection(t_ray *ray, t_player player)
{
	float	wall;

	if (ray->side == EAST || ray->side == WEST)
		wall = player.pos.y + ray->dist * ray->dir.y;
	else
		wall = player.pos.x + ray->dist * ray->dir.x;
	return (modff(wall, &(float){0}));
}

t_texture	*get_texture(t_ray *ray, t_game *game)
{
	if (ray->side == EAST || ray->side == WEST)
	{
		if (ray->dir.x > 0)
			return (&game->textures[EAST]);
		else
			return (&game->textures[WEST]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->textures[NORTH]);
		else
			return (&game->textures[SOUTH]);
	}
}
