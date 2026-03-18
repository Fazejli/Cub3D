/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:34 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/18 14:45:02 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

#include <stdio.h>

static int	validate_asset_colors(t_assets *a)
{
	if (!a->ceiling)
	{
		dprintf(2, "Colors: warning: 'ceiling' color not set. Setting to magenta\n");
		a->ceiling = RGB_INVALID;
	}
	if (!a->floor)
	{
		dprintf(2, "Colors: warning: 'floor' color not set. Setting to magenta\n");
		a->floor = RGB_INVALID;
	}
	return (0);
}

static int	no_valid_colors_and_textures(t_assets *a, size_t pos)
{
	a->tiles[pos].colors[DIR_INVALID] = 255 << 16 | 255;
	if (a->tiles[pos].flags & TILE_F_RAY_BLOCK &&
		!a->tiles[pos].textures[DIR_DEFAULT] &&
		!a->tiles[pos].colors[DIR_DEFAULT] &&
		((!a->tiles[pos].textures[DIR_NORTH]
		&& !a->tiles[pos].colors[DIR_NORTH])
		|| (!a->tiles[pos].textures[DIR_SOUTH]
		&& !a->tiles[pos].colors[DIR_SOUTH])
		|| (!a->tiles[pos].textures[DIR_EAST]
		&& !a->tiles[pos].colors[DIR_EAST])
		|| (!a->tiles[pos].textures[DIR_WEST]
		&& !a->tiles[pos].colors[DIR_WEST])))
		return (dprintf(2, "Colors: warning: No default / full NSWE texture.s nor color.s set for tile '%c'\n", (char)pos + 32), 1);
	return (0);
}

static int	validate_tile_colors(t_assets *a)
{
	size_t		i;

	i = 0;
	while (i < 96)
	{
		if (a->tiles[i].flags == TILE_F_NONE)
		{
			i++;
			continue;
		}
		no_valid_colors_and_textures(a, i);
		i++;
	}
	return (0);
}

int	validate_colors(t_assets *a)
{
	validate_asset_colors(a);
	validate_tile_colors(a);
	return (0);
}
