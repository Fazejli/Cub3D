/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:26:09 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 19:29:22 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	flood_fill_check(char **map, int x, int y)
{
	char	c;
	int		height;
	int		width;

	height = get_height(map);
	width = get_width(map);
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	c = get_map_char(map, x, y);
	if (c == '\n' || c == '\0')
		return (0);
	if (c == '1' || c == ' ' || c == 'V')
		return (1);
	if (!is_valid_char(c))
		return (0);
	map[y][x] = 'V';
	if (!flood_fill_check(map, x + 1, y))
		return (0);
	if (!flood_fill_check(map, x - 1, y))
		return (0);
	if (!flood_fill_check(map, x, y + 1))
		return (0);
	if (!flood_fill_check(map, x, y - 1))
		return (0);
	return (1);
}
