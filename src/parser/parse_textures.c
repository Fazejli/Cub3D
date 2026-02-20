/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:24:31 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:06:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	assign_texture(t_data *data, char *path, int type)
{
	if (type == 1)
		data->t_north = path;
	if (type == 2)
		data->t_south = path;
	if (type == 3)
		data->t_west = path;
	if (type == 4)
		data->t_east = path;
}

char	*extract_path(char *line)
{
	uint32_t	i;
	uint32_t	start;
	uint32_t	end;
	char		*path;

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	end = i;
	while (end > start && ft_isspace(line[end - 1]))
		end --;
	path = ft_substr(line, start, end - start);
	return (path);
}

int	check_duplicate_texture(t_data *data, int type)
{
	if (type == 1 && data->t_north != NULL)
		return (1);
	if (type == 2 && data->t_south != NULL)
		return (1);
	if (type == 3 && data->t_west != NULL)
		return (1);
	if (type == 4 && data->t_east != NULL)
		return (1);
	return (0);
}

int	parse_single_texture(t_data *data, char *line, int type)
{
	char	*path;
	int		fd;

	if (check_duplicate_texture(data, type))
		return (mess_error("Duplicate texture"));
	path = extract_path(line);
	if (!path || !*path)
		return (mess_error("Path extraction failed"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (mess_error("Texture file not found"));
	}
	close(fd);
	assign_texture(data, path, type);
	return (0);
}

int	parse_textures(t_data *data, char *line, int type)
{
	if (type >= 1 && type <= 4)
		return (parse_single_texture(data, line, type));
	else if (type == 5)
		return (parse_color(data, line, 'F'));
	else if (type == 6)
		return (parse_color(data, line, 'C'));
	else if (type == 7)
		return (0);
	return (mess_error("Invalid element's identifier"));
}
