#include "../../inc/cub3d.h"

int	get_width(char **map)
{
	int	max_width;
	int	width;
	int	i;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	check_all_elements(t_data *data)
{
	if (!data->t_north || !data->t_south
		|| !data->t_west || !data->t_east)
		return (0);
	if (data->floor_color == -1 || data->ceiling_color == -1)
		return (0);
	return (1);
}

int	check_empty_lines_after(int fd)
{
	char	*line;

	while (1)
	{
		line = gnl(fd);
		if (!line)
			return (1);
		if (!ft_is_empty(line))
		{
			free(line);
			return (mess_error("Empty line in map"));
		}
		free(line);
	}
	return (1);
}

char	**copy_map(char **map)
{
	char	**copy;
	int		i;
	int		height;

	height = get_height(map);
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
