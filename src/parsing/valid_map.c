/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:26:09 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/17 19:20:54 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static const char	g_dir_to_char[] = {
	[EAST] = 'E',
	[NORTH] = 'N',
	[WEST] = 'W',
	[SOUTH] = 'S',
};

int	flood_fill(t_pos *player_pos, char **map, int i, int j)
{
	if (map[i][j] == g_dir_to_char[player_pos->dir])
	{
		player_pos->x = j;
		player_pos->y = i;
		if (!flood_fill_check(map, j, i))
			return (mess_error("Map not closed"));
	}
	return (0);
}

int	find_player(t_pos *player_pos, char **map)
{
	int	i;
	int	j;

	// if (!player_pos || !player_pos->dir)
	// 	return (mess_error("Player not found"));
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (flood_fill(player_pos, map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	valid_map(t_data *data)
{
	int		i;
	int		height;
	int		status;
	char	**map_cpy;

	i = 0;
	// todo check for player existence
	// if (data->player_pos.dir == DIR_NONE)
	// 	return (mess_error("No player in map"));
	height = get_height(data->map);
	while (i < height)
	{
		if (!data->map[i])
			return (mess_error("Invalid map"));
		i++;
	}
	map_cpy = copy_map(data->map);
	if (!map_cpy)
		return (mess_error("Malloc failed"));
	status = find_player(&data->player_pos, map_cpy);
	free_map(map_cpy);
	return (status);
}
