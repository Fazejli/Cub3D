/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:26:09 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/20 01:56:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>

static const char	g_dir_to_char[] = {
[EAST] = 'E',
[NORTH] = 'N',
[WEST] = 'W',
[SOUTH] = 'S',
};

static int	flood_fill(t_pos *player_pos, char **map, uint32_t x, uint32_t y)
{
	if (map[y][x] == g_dir_to_char[player_pos->dir])
	{
		player_pos->x = (float)x;
		player_pos->y = (float)y;
		if (!flood_fill_check(map, x, y))
			return (mess_error("Map not closed"));
	}
	return (0);
}

int	find_player(t_pos *player_pos, char **map)
{
	uint32_t	x;
	uint32_t	y;

	// if (!player_pos || !player_pos->dir)
	// 	return (mess_error("Player not found"));
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (flood_fill(player_pos, map, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_map(t_data *data)
{
	uint32_t	y;
	uint32_t	height;
	int			status;
	char		**map_cpy;

	y = 0;
	// todo check for player existence
	// if (data->player_pos.dir == DIR_NONE)
	// 	return (mess_error("No player in map"));
	height = get_height(data->map);
	while (y < height)
	{
		if (!data->map[y])
			return (mess_error("Invalid map"));
		y++;
	}
	map_cpy = copy_map(data->map);
	if (!map_cpy)
		return (mess_error("Malloc failed"));
	status = find_player(&data->player_pos, map_cpy);
	free_map(map_cpy);
	return (status);
}
