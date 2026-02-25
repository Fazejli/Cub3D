/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:10:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/25 03:18:36 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mapping.h"
#include "mapping_internal.h"

static void	fill_map(char *map_data, const char *map_start, t_vec3u size)
{
	const char	*ptr;
	size_t		line;
	size_t		height;

	ptr = map_start;
	height = 0;
	while (height < size.z)
	{
		line = 0;
		while (!is_eol(ptr[line]) && size.x > line)
			line++;
		while (!is_eol(ptr[line]) && size.y + 1 >= line)
			*(map_data++) = ptr[line++];
		while (!is_eol(ptr[line]))
			line++;
		ptr += line;
		if (*ptr == '\n')
			ptr++;
		while (size.x > line++)
			continue ;
		while (size.y + 1 >= line++)
			*(map_data++) = ' ';
		height++;
	}
}
static uint32_t	find_player(t_map map)
{
	uint32_t	i;
	bool		found;

	i = 0;
	found = false;
	while (i < map.width * map.height)
	{
		if (map.data[i] == 'N' || map.data[i] == 'S'
			|| map.data[i] == 'E' || map.data[i] == 'W')
		{
			if (found)
				return (UINT32_MAX);
			found = true;
		}
		i++;
	}
	if (!found)
		return (UINT32_MAX);
	return (i);
}

static t_map	extract_map(const char *map_start)
{
	t_map		map;
	t_vec3u		size;
	uint32_t	width;

	map = (t_map){0};
	size = get_map_size(map_start);
	if (size.z == 0 || size.x > size.y)
		return ((t_map){.error = ERR_MAP});
	width = size.y - size.x + 1; //rm 1 ?
	map.data = malloc(width * size.z + 1);
	if (!map.data)
		return ((t_map){.error = ERR_PERROR});
	fill_map(map.data, map_start, size);
	map.width = width;
	map.height = size.z;
	map.player = find_player(map);
	if (map.player == UINT32_MAX)
	{
		free(map.data);
		return ((t_map){.error = ERR_MAP});
	}
	map.error = ERR_NONE;
	return (map);
}

static bool	is_enclosed_by_walls(t_map map)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	while (i < map.width * map.height)
	{
		x = i % map.width;
		y = i / map.width;
		if (is_walkable(map.data[i]))
		{
			if (x == 0 || x == map.width - 1
				|| y == 0 || y == map.height - 1)
				return (false);
			if (!is_map_char(map.data[i - 1])
				|| !is_map_char(map.data[i + 1])
				|| !is_map_char(map.data[i - map.width])
				|| !is_map_char(map.data[i + map.width]))
				return (false);
		}
		i++;
	}
	return (true);
}

#include <stdio.h>

t_map	get_map(const char *file_path)
{
	t_file		file;
	t_map		map;
	const char	*map_start;

	file = map_file(file_path);
	if (file.error != ERR_NONE)
	{
		dprintf(2, "Could not map file\n");
		return ((t_map){.error = file.error});
	}
	if (!file.data || file.size <= 0)
	{
		dprintf(2, "Invalid file to get map from\n");
		unmap_file(&file);
		return ((t_map){.error = ERR_UNKNOWN}); //error to be added
	}
	map_start = find_map(file);
	if (!map_start)
	{
		dprintf(2, "Could not find map start\n");
		unmap_file(&file);
		return ((t_map){.error = ERR_MAP}); //error to be added
	}
	map = extract_map(map_start);
	unmap_file(&file);
	if (map.error)
	{
		dprintf(2, "Could not extract map\n");
		return ((t_map){.error = ERR_PERROR});
	}
	if (!is_enclosed_by_walls(map))
	{
		dprintf(2, "Map is not enclosed by walls\n");
		free(map.data);
		return ((t_map){.error = ERR_MAP});
	}
	return (map);
}

// #include <unistd.h>

// int	main(int argc, char **argv)
// {
// 	t_map	map;

// 	if (argc != 2)
// 		return (dprintf(2, "Invalid args\n"));

// 	map = get_map(argv[1]);
// 	if (map.error != ERR_NONE)
// 		return (dprintf(2, "Could not get map\n"));

// 	size_t	i = 0;
// 	printf("Map specs : width %u, height %u\n\n", map.width, map.height);
// 	printf("Map data full dump [%s]:\n", map.data);
// 	while (map.data[i])
// 	{
// 		write(1, &map.data[i], map.width);
// 		write(1, "\n", 1);
// 		i += map.width;
// 	}
	
// 	free(map.data);
// 	return (0);
// }
