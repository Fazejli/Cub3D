/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:25:46 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/17 15:38:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	check_empty_lines_after(int fd)
{
	char	*line;

	while (1)
	{
		line = gnl(fd);
		if (!line)
			return (0);
		if (!ft_is_empty(line))
		{
			free(line);
			return (mess_error("Empty line in map"));
		}
		free(line);
	}
	return (0);
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
