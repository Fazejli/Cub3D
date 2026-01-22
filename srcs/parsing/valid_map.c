#include "../../inc/cub3d.h"

char	get_map_char(char **map, int x, int y)
{
	if (y < 0 || !map[y])
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

int	flood_fill_check(char **map, int x, int y, int w, int h)
{
	char	c;

	if (y < 0 || y >= h || x < 0)
		return (0);
	c = get_map_char(map, x, y);
	if (c == ' ' || c == '\n' || c == '\0')
		return (0);
	if (c == '1' || c == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill_check(map, x + 1, y, w, h))
		return (0);
	if (!flood_fill_check(map, x - 1, y, w, h))
		return (0);
	if (!flood_fill_check(map, x, y + 1, w, h))
		return (0);
	if (!flood_fill_check(map, x, y - 1, w, h))
		return (0);
	return (1);
}

int	find_player_and_validate(t_data *data, char **map_copy)
{
	int	i;
	int	j;
	int	w;
	int	h;

	w = get_map_width(data->map);
	h = get_map_height(data->map);
	i = -1;
	while (map_copy[++i])
	{
		j = -1;
		while (map_copy[i][++j])
		{
			if (map_copy[i][j] == data->player_pos->pos)
			{
				data->player_pos->x = j;
				data->player_pos->y = i;
				if (!flood_fill_check(map_copy, j, i, w, h))
					return (mess_error("Map not closed"));
				return (0);
			}
		}
	}
	return (mess_error("Player not found"));
}

int	check_all_elements_present(t_data *data)
{
	if (!data->t_north || !data->t_south
		|| !data->t_west || !data->t_east)
		return (0);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (0);
	return (1);
}

int	validate_map(t_data *data)
{
	char	**map_copy;
	int		result;

	if (!data->player_pos)
		return (mess_error("No player position"));
	map_copy = copy_map(data->map);
	if (!map_copy)
		return (mess_error("Malloc failed"));
	result = find_player_and_validate(data, map_copy);
	free_map(map_copy);
	return (result);
}