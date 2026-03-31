/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 15:37:15 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 19:55:36 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets.h"

#ifdef DEBUG

# include <stddef.h>
# include <stdio.h>

static void	debug_print_id_and_flags(char id, t_tile_flags flags)
{
	printf("\n- Tile '%c':", id);
	if (flags == TILE_F_NONE)
	{
		printf(" NONE\n");
		return ;
	}
	if (flags & TILE_F_VOID)
		printf(" VOID");
	if (flags & TILE_F_SOLID)
		printf(" SOLID");
	if (flags & TILE_F_WALKABLE)
		printf(" WALKABLE");
	if (flags & TILE_F_RAY_BLOCK)
		printf(" RAY_BLOCK");
	if (flags & TILE_F_DOOR)
		printf(" DOOR");
	if (flags & TILE_F_PLAYER)
		printf(" PLAYER");
	printf("\n");
}

static void	debug_print_tile(const t_tile *tile, char id)
{
	debug_print_id_and_flags(id, tile->flags);
	if (tile->textures[DIR_DEFAULT])
		printf("~ D texture defined, fc: %d\n", tile->frame_count[DIR_DEFAULT]);
	if (tile->textures[DIR_NORTH])
		printf("~ N texture defined, fc: %d\n", tile->frame_count[DIR_NORTH]);
	if (tile->textures[DIR_SOUTH])
		printf("~ S texture defined, fc: %d\n", tile->frame_count[DIR_SOUTH]);
	if (tile->textures[DIR_WEST])
		printf("~ W texture defined, fc: %d\n", tile->frame_count[DIR_WEST]);
	if (tile->textures[DIR_EAST])
		printf("~ E texture defined, fc: %d\n", tile->frame_count[DIR_EAST]);
	if (tile->colors[DIR_DEFAULT] != RGB_INVALID)
		printf("~ D color defined: 0x%06X\n", tile->colors[DIR_DEFAULT]);
	if (tile->colors[DIR_NORTH] != RGB_INVALID)
		printf("~ N color defined: 0x%06X\n", tile->colors[DIR_NORTH]);
	if (tile->colors[DIR_SOUTH] != RGB_INVALID)
		printf("~ S color defined: 0x%06X\n", tile->colors[DIR_SOUTH]);
	if (tile->colors[DIR_WEST] != RGB_INVALID)
		printf("~ W color defined: 0x%06X\n", tile->colors[DIR_WEST]);
	if (tile->colors[DIR_EAST] != RGB_INVALID)
		printf("~ E color defined: 0x%06X\n", tile->colors[DIR_EAST]);
}

static void	debug_print_map(const t_map *map)
{
	size_t	x;
	size_t	y;

	printf("\n- Size: %zu * %zu\n\n", map->width, map->height);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
			printf("%c", map->data[y * map->width + x++] + 32);
		printf("\n");
		y++;
	}
}

void	debug_print_assets(t_assets *a)
{
	size_t	i;

	printf("\t\t- ASSETS -\n");
	printf("\nTiles:\n");
	i = 0;
	while (i < 96)
	{
		if (a->tiles[i].flags != TILE_F_NONE)
			debug_print_tile(&a->tiles[i], (char)(i + 32));
		i++;
	}
	printf("\nMap:\n");
	debug_print_map(&a->map);
	printf("\nOther:\n");
	if (a->asset_tex[TEX_INVALID])
		printf("\t-Invalid texture defined\n");
	if (a->asset_tex[TEX_FLOOR])
		printf("\t-Floor texture defined\n");
	if (a->asset_tex[TEX_CEILING])
		printf("\t-Ceiling texture defined\n");
	if (a->floor != RGB_INVALID)
		printf("\t-Floor color defined: 0x%06X\n", a->floor);
	if (a->ceiling != RGB_INVALID)
		printf("\t-Ceiling color defined: 0x%06X\n", a->ceiling);
	printf("\n");
}

#else

void	debug_print_assets(t_assets *a)
{
	(void)a;
	return ;
}

#endif
