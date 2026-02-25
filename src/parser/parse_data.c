/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:21:50 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/25 04:07:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include "utils/error.h"

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
				return (print_error(loc(F, L), ERR_UNKNOWN, 99));
			}
		}
		free(line);
	}
	if (!check_all_elements(data))
		return (print_error(loc(F, L), ERR_UNKNOWN, 99));
	return (0);
}

void	init_data(t_data *data)
{
	data->t_north = NULL;
	data->t_south = NULL;
	data->t_west = NULL;
	data->t_east = NULL;
	data->floor_color = -1u;
	data->ceiling_color = -1u;
	data->map = NULL;
}

static int	check_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(loc(F, L), ERR_PERROR, errno));
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
			return (print_error(loc(F, L), ERR_UNKNOWN, 99));
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
