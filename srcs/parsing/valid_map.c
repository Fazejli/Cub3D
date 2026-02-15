/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:26:09 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 16:47:39 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_all_elements(t_data *data)
{
	if (!data->t_north || !data->t_south || !data->t_west || !data->t_east)
		return (0);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (0);
	return (1);
}

char	get_map_char(char **map, int x, int y)
{
	if (y < 0 || !map[y])
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

//IL faut modifier pour avoir 4 arg (respect de la norme)
int	flood_fill_check(char **map, int x, int y, int width, int height)
{
	char	c;

	if (y < 0 || y >= height || x < 0)
		return (0);
	c = get_map_char(map, x, y);
	if (c == '\n' || c == '\0')
		return (0);
	if (c == '1' || c == ' ' || c == 'V')
		return (1);
	if (!is_valid_char(c))
		return (0);
	map[y][x] = 'V';
	if (!flood_fill_check(map, x + 1, y, width, height))
		return (0);
	if (!flood_fill_check(map, x - 1, y, width, height))
		return (0);
	if (!flood_fill_check(map, x, y + 1, width, height))
		return (0);
	if (!flood_fill_check(map, x, y - 1, width, height))
		return (0);
	return (1);
}

int	find_player(t_pos *player_pos, char **map)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	if (!player_pos || !player_pos->dir)
		return (mess_error("Player not found"));
	width = get_width(map);
	height = get_height(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == player_pos->dir)
			{
				player_pos->x = j;
				player_pos->y = i;
				if (!flood_fill_check(map, j, i, width, height))
					return (mess_error("Map not closed"));
				return (0);
			}
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
	if (!data->player_pos || !data->player_pos->dir)
		return (mess_error("No player in map"));
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
	status = find_player(data->player_pos, map_cpy);
	free_map(map_cpy);
	return (status);
}
