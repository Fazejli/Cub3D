/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 02:33:24 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 03:03:24 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mapping_internal.h"

static t_vec3u	get_line_bounds(const char *line)
{
	t_vec3u		line_bounds;
	const char	*ptr;
	size_t		col;
	bool		has_map_char;


	line_bounds = (t_vec3u){UINT32_MAX, 0, 0};
	ptr = line;
	col = 0;
	has_map_char = false;
	while (!is_eol(ptr[col]))
	{
		if (is_map_char(ptr[col]))
		{
			if (!has_map_char)
				line_bounds.x = col;
			line_bounds.y = col;
			has_map_char = true;
		}
		else if (ptr[col] != ' ')
			return ((t_vec3u){0, 0, UINT32_MAX});
		col++;
	}
	line_bounds.z = col;
	return (line_bounds);
}

static uint32_t	get_map_height(const char *map_start)
{
	uint32_t	height;
	uint32_t	last_valid_line;
	size_t		col;
	bool		has_map_char;

	height = 0;
	last_valid_line = 0;
	col = 0;
	while (map_start[col])
	{
		has_map_char = false;
		while (!is_eol(map_start[col]))
		{
			if (is_map_char(map_start[col]))
				has_map_char = true;
			col++;
		}
		if (has_map_char)
			last_valid_line = height + 1;
		if (map_start[col] == '\n')
			col++;
		height++;
	}
	return (last_valid_line);
}

static	size_t	update_ptr(const char *ptr, size_t offset)
{
	if (ptr[offset] == '\n')
		return (offset + 1);
	else
		return (offset);
}

t_vec3u	get_map_size(const char *map_start)
{
	t_vec3u		size;
	t_vec3u		line_bounds;
	const char	*ptr;

	size = (t_vec3u){UINT32_MAX, 0, 0};
	ptr = map_start;
	while (*ptr)
	{
		line_bounds = get_line_bounds(ptr);
		if (line_bounds.z == UINT32_MAX)
			return ((t_vec3u){0, 0, 0});
		else
		{
			if (line_bounds.x < size.x)
				size.x = line_bounds.x;
			if (line_bounds.y > size.y)
				size.y = line_bounds.y;
		}
		ptr += update_ptr(ptr, line_bounds.z);
	}
	if (size.x == UINT32_MAX)
		return ((t_vec3u){0, 0, 0});
	size.z = get_map_height(map_start);
	return (size);
}
