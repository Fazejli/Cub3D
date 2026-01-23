#include "../../inc/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_player_pos(t_data *data, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->player_pos != NULL)
			return (mess_error("Multiple players"));
		data->player_pos = malloc(sizeof(t_pos));
		if (!data->player_pos)
			return (mess_error("Malloc failed"));
		data->player_pos->pos = c;
		data->player_pos->x = 0;
		data->player_pos->y = 0;
	}
	return (0);
}

int	store_map_lines(t_data *data, char *first_line)
{
	char	*line;
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * 1000);
	if (!temp)
		return (mess_error("Malloc failed"));
	temp[0] = ft_strdup(first_line);
	i = 1;
	while (1)
	{
		line = gnl(data->fd);
		if (!line || ft_is_empty(line))
		{
			if (line && !check_empty_lines_after(data->fd))
				return (free(line), free_map(temp), 1);
			break ;
		}
		temp[i++] = line;
	}
	temp[i] = NULL;
	data->map = temp;
	return (free(line), 0);
}

int	check_map_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
			return (mess_error("Invalid map char"));
		if (check_player_pos(data, line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_map(t_data *data, char *first_line)
{
	int	i;

	if (check_map_line(first_line, data))
		return (1);
	if (store_map_lines(data, first_line))
		return (1);
	i = 0;
	while (data->map[i])
	{
		if (check_map_line(data->map[i], data))
			return (1);
		i++;
	}
	return (0);
}
