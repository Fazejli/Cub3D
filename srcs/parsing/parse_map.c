/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:23:24 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 18:38:57 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (data->player_pos && data->player_pos->dir)
			return (mess_error("Multiple players"));
		data->player_pos = malloc(sizeof(t_pos));
		if (!data->player_pos)
			return (mess_error("Malloc failed"));
		data->player_pos->dir = c;
		data->player_pos->x = 0;
		data->player_pos->y = 0;
	}
	return (0);
}

static void	free_temp_map(char **temp, int count)
{
	int	i;

	if (!temp)
		return ;
	i = 0;
	while (i < count)
	{
		if (temp[i])
			free(temp[i]);
		i++;
	}
	free(temp);
}

/*void	clear_line(char *str)
{
	int len = ft_strlen(str);
	int i = 0;
	char dst[len];
	while (str[i] && i < len)
	{
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isspace(str[i]))
			dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	str = dst;
}*/

int	store_map_lines(t_data *data, char *first_line)
{
	char	*line;
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * 1000);
	if (!temp)
		return (mess_error("Malloc failed"));
	temp[0] = ft_strdup(first_line);
	if (!temp[0])
	{
		free(temp);
		return (mess_error("Malloc failed"));
	}
	i = 1;
	while (1)
	{
		line = gnl(data->fd);
		if (!line || ft_is_empty(line))
		{
			if (line && check_empty_lines_after(data->fd))
			{
				free(line);
				free_temp_map(temp, i);
				return (1);
			}
			free(line);
			break ;
		}
		temp[i] = ft_strdup(line);
		if (!temp[i])
		{
			free(line);
			free_temp_map(temp, i);
			return (mess_error("Malloc failed"));
		}
		free(line);
		i++;
	}
	temp[i] = NULL;
	data->map = temp;
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
