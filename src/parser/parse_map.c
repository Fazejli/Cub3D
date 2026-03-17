/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:41:09 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 11:46:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils/t_str.h"
#include "utils/utils.h"

#include "parser_internal.h"

#include <stdio.h>

static int	get_map_size(t_parser p, size_t	*width, size_t *height, size_t *offset)
{
	t_str	line;
	size_t	gap;
	size_t	min_line;
	size_t	max_line;

	gap = 1;
	while (next_line(&p, &line, false, false))
	{
		back_trim_str(&line);
		max_line = line.len;
		front_trim_str(&line);
		min_line = max_line - line.len;
		if (line.len == 0)
		{
			if (*height != 0)
				gap++;
			continue ;
		}
		if (*offset > min_line)
			*offset = min_line;
		if (*width < max_line)
			*width = max_line;
		*height += gap;
		gap = 1;
	}
	*width -= *offset;
	if (*height == 0 || *width == 0)
		return (1);
	return (0);
}

int	populate_map(t_assets *a, t_parser p, size_t offset)
{
	t_str		line;
	size_t		x;
	size_t		y;
	char		tile;

	y = 0;
	while (next_line(&p, &line, false, true))
	{
		if (line.len == 0 && y == 0)
			continue ;
		if (line.len > offset)
		{
			line.ptr += offset;
			line.len -= offset;
		}
		else
			line.len = 0;
		x = 0;
		while (x < a->map.width)
		{
			
			if (x < line.len)
				tile = line.ptr[x];
			else
			 	tile = ' ';
			if (!is_printable(tile))
				return (dprintf(2, "Map: non printable tile found at position x=%zu, y=%zu\n", x, y), 1);
			if (a->tiles[(uint32_t)tile - 32].flags == TILE_F_NONE)
				return (dprintf(2, "Map: non valid tile found at position x=%zu, y=%zu: [%c]\n", x, y, tile), 1);
			a->map.data[y * a->map.width + x] = (uint8_t)tile - 32;
			x++;
		}
		y++;
	}
	return (0);
}

int	parse_map(t_assets *a, t_parser p)
{
	size_t	offset;

	a->map.width = 0;
	a->map.height = 0;
	offset = SIZE_MAX;
	if (get_map_size(p, &a->map.width, &a->map.height, &offset))
		return (dprintf(2, "Map: map size invalid\n"), 1);
	printf("Width=%zu, Height=%zu, offset=%zu\n", a->map.width, a->map.height, offset);
	a->map.data = (uint8_t *)malloc(sizeof(uint8_t) * (a->map.width * a->map.height));
	if (!a->map.data)
		return (1);
	if (populate_map(a, p, offset))
	{
		free(a->map.data);
		a->map.data = NULL;
		return (1);
	}
	return (0);
}
