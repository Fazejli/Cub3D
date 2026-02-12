/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:21:50 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 13:35:12 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	find_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (4);
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (5);
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (6);
	return (0);
}

int	handle_element(t_data *data, char *line, int *count)
{
	int	type;

	type = find_type(line);
	if (type == 0 || parse_textures(data, line, type))
		return (-1);
	if (type > 0)
		(*count)++;
	return (0);
}

int	parse_sections(t_data *data)
{
	char	*line;
	int		compt;

	compt = 0;
	while (compt < 6)
	{
		line = gnl(data->fd);
		if (!line)
			return (1);
		if (!ft_is_empty(line))
		{
			if (handle_element(data, line, &compt) == -1)
			{
				free(line);
				return (mess_error("Invalid element"));
			}
		}
		free(line);
	}
	if (!check_all_elements(data))
		return (mess_error("Missing elements."));
	return (0);
}

void	init_data(t_data *data)
{
	data->t_north = NULL;
	data->t_south = NULL;
	data->t_west = NULL;
	data->t_east = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	data->map = NULL;
	data->player_pos = NULL;
}

int	parse_data(t_data *data)
{
	char	*line;

	init_data(data);
	if (parse_sections(data))
		return (1);
	while (1)
	{
		line = gnl(data->fd);
		if (!line)
			return (mess_error("No map found"));
		if (!ft_is_empty(line))
		{
			if (parse_map(data, line))
				return (free(line), 1);
			free(line);
			break ;
		}
		free(line);
	}
	if (valid_map(data))
		return (1);
	return (0);
}
