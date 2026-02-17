/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:21:50 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/17 15:38:25 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static int	check_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (mess_error(NULL));
	data->fd = fd;
	return (0);
}

int	parse_data(t_data *data, char *filename)
{
	char	*line;

	if (check_file(data, filename))
		return (1);
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
