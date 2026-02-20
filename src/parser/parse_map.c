/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:23:24 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:10:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

enum e_dir	g_char_to_dir[] = {
['N'] = NORTH,
['W'] = WEST,
['S'] = SOUTH,
['E'] = EAST,
};

int	check_player_pos(t_data *data, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		// todo check for multiple players
		data->player_pos.dir = g_char_to_dir[(int)c];
		data->player_pos.x = 0;
		data->player_pos.y = 0;
	}
	return (0);
}

int	store_map_lines(t_data *data, char **temp, int i)
{
	char	*line;

	while (1)
	{
		line = gnl(data->fd);
		if (!line || ft_is_empty(line))
		{
			if (line && check_empty_lines_after(data->fd))
			{
				free(line);
				return (free_temp_map(temp, i), 1);
			}
			free(line);
			break ;
		}
		temp[i] = ft_strdup(line);
		if (!temp[i])
			return (free(line), free_temp_map(temp, i), 1);
		free(line);
		i++;
	}
	temp[i] = NULL;
	return (0);
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
	char	**temp;
	int		i;

	if (check_map_line(first_line, data))
		return (1);
	temp = malloc(sizeof(char *) * 10000);
	if (!temp)
		return (mess_error("Malloc failed"));
	temp[0] = ft_strdup(first_line);
	if (!temp[0])
		return (free(temp), mess_error("Malloc failed"));
	if (store_map_lines(data, temp, 1))
		return (1);
	data->map = temp;
	i = 0;
	while (data->map[i])
	{
		if (check_map_line(data->map[i], data))
			return (1);
		i++;
	}
	return (0);
}
