/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:31:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/17 11:56:04 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "assets/assets.h"
#include "utils/t_str.h"

#include "parser_internal.h"

static uint32_t	parse_tile_flags(t_str value)
{
	if (value.len == 4 && !strncmp(value.ptr, "wall", 4))
		return (TILE_F_WALL);
	if (value.len == 6 && !strncmp(value.ptr, "player", 6))
		return (TILE_F_PLAYER | TILE_F_WALKABLE);
	if (value.len == 4 && !strncmp(value.ptr, "door", 4))
		return (TILE_F_DOOR | TILE_F_RAY_BLOCK);
	if (value.len == 5 && !strncmp(value.ptr, "floor", 5))
		return (TILE_F_WALKABLE);
	return (TILE_F_NONE);
}

static bool	add_tile(t_assets *assets, char id, t_tile_flags flags)
{
	t_tile	*tile;

	if (assets->tiles[(unsigned char)id - 32].flags)
		return (false); //error: duplicate tile id
	tile = &assets->tiles[(unsigned char)id - 32];
	tile->flags = (t_tile_flags)flags;
	return (true);
}

#include <stdio.h>

int	parse_tiles(t_assets *a, t_parser p)
{
	t_str			line;
	t_str			key;
	t_str			value;
	t_tile_flags	flags;

	while (next_line(&p, &line, true, true))
	{
		if (line.len == 0)
			continue;
		if (!split_key_value(line, &key, &value))
			return (dprintf(2, "Tiles: could not find seperate key and value: [%.*s]\n", (int)line.len, line.ptr), 1);
		if (!is_tile_key(key))
			return (dprintf(2, "Tiles: key is not a tile: [%.*s]\n", (int)key.len, key.ptr), 1);
		if (value.len == 0)
			return (dprintf(2, "Tiles: no flags specified for tile '%c'.\n", *key.ptr), 1);
		flags = parse_tile_flags(value);
		if (flags == TILE_F_NONE)
			return (dprintf(2, "Tiles: specified flags for tile '%c' unknown: [%.*s]\n", *key.ptr, (int)value.len, value.ptr), 1);
		if (!add_tile(a, key.ptr[0], flags))
			return (dprintf(2, "Tiles: tile '%c' already has previous attribution.\n", *key.ptr), 1);
	}
	if (!add_tile(a, ' ', TILE_F_VOID)) //add default void tile
		return (dprintf(2, "Tiles: tile '%c' already has previous attribution.\n", *key.ptr), 1);
	return (0);
}
