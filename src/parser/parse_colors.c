/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:29:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 11:45:34 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utils/t_str.h"

#include "parser_internal.h"

#include <stdio.h>

static int	add_tile_color(t_assets *a, t_str key, t_str option, t_str value)
{
	uint32_t	rgb;
	t_tile		*tile;
	uint32_t	dir;

	tile = &a->tiles[(unsigned char)key.ptr[0] - 32];
	if (tile == NULL)
		return (dprintf(2, "Colors: tile '%c' has not been initialized\n", *key.ptr), 1);
	dir = parse_dir_option(option);
	if (dir >= DIR_COUNT)
		return (dprintf(2, "Colors: orientation not valid: [%.*s]\n", (int)option.len, option.ptr), 1);
	if (tile->colors[dir] != 0)
		return (dprintf(2, "Colors: color for tile '%c' already has previous attribution\n", *key.ptr), 1);
	rgb = parse_rgb(value);
	if (!rgb)
		return (dprintf(2, "Colors: invalid color for tile '%c': [%.*s]\n", *key.ptr, (int)value.len, value.ptr), 1);
	tile->colors[dir] = rgb;
	return (0);
}

static int add_asset_color(t_assets *a, t_str key, t_str option, t_str value)
{
	(void)option; //asset colors do not support options yet

	uint32_t	*color;
	uint32_t	rgb;

	if (key.len < 2)
		return (dprintf(2, "Colors: key not valid: [%.*s]\n", (int)key.len, key.ptr), 1);
	if (key.len == 7 && strncmp(key.ptr, "ceiling", 7) == 0)
		color = &a->ceiling;
	else if (key.len == 5 && strncmp(key.ptr, "floor", 5) == 0)
		color = &a->floor;
	else
		return (dprintf(2, "Colors: could not find valid color address: [%.*s]\n", (int)key.len, key.ptr), 1);

	if (*color != 0)
		return (dprintf(2, "Colors: color for asset '%.*s' already has previous attribution.\n", (int)key.len, key.ptr), 1);
	rgb = parse_rgb(value);
	if (!rgb)
		return (dprintf(2, "Colors: invalid color for asset '%.*s': [%.*s]\n", (int)key.len, key.ptr, (int)value.len, value.ptr), 1);
	*color = rgb;
	return (0);
}

int	parse_colors(t_assets *a, t_parser p)
{
	t_str		line;
	t_str		key;
	t_str		value;
	t_str		option;
	int			status;

	while (next_line(&p, &line, true, true))
	{
		if (line.len == 0)
			continue;
		if (!split_key_value(line, &key, &value))
			return (1); //error
		if (key.len == 0 || value.len == 0)
			return (1); //error, key and value must be non-empty
		split_key_option(key, &key, &option);
		if(is_tile_key(key))
			status = add_tile_color(a, key, option, value);
		else
			status = add_asset_color(a, key, option, value);
		if (status)
			return (status);
	}
	return (0);
}
