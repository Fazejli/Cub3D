/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:43 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/15 19:59:47 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

#include <stdio.h>

static int	validate_asset_textures(t_assets *a)
{
	if (!a->invalid)
		dprintf(2, "Textures: warning: 'invalid' texture not set\n");
	return (0);
}

static int	no_valid_textures(t_assets *a, size_t pos)
{
	if (a->invalid)
		a->tiles[pos].textures[DIR_INVALID] = a->invalid;
	if (a->tiles[pos].flags & TILE_F_RAY_BLOCK &&
		!a->tiles[pos].textures[DIR_DEFAULT] &&
		(!a->tiles[pos].textures[DIR_NORTH]
		|| !a->tiles[pos].textures[DIR_SOUTH]
		|| !a->tiles[pos].textures[DIR_WEST]
		|| !a->tiles[pos].textures[DIR_EAST]))
	{
		dprintf(2, "Textures: warning: No default / full NSWE texture.s set for tile '%c'\n", (char)pos + 32);
		return (1);
	}
	return (0);
}

static int	validate_tile_textures(t_assets *a)
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
		no_valid_textures(a, i);
		i++;
	}
	return (0);
}

int	validate_textures(t_assets *a)
{
	validate_asset_textures(a);
	validate_tile_textures(a);
	return (0);
}
