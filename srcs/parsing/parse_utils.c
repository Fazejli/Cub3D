/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:25:46 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 12:26:00 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_atoi_rgb(const char *str, int *error)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	*error = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (0);
		i++;
	}
	*error = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] != ',' && str[i] != '\n')
		*error = 1;
	return (result);
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
