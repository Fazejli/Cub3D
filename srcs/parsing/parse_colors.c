/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 14:24:26 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb(char **rgb, int *r, int *g, int *b)
{
	int	error;

	*r = ft_atoi_rgb(rgb[0], &error);
	if (error)
		return (mess_error("Invalid R value"));
	*g = ft_atoi_rgb(rgb[1], &error);
	if (error)
		return (mess_error("Invalid G value"));
	*b = ft_atoi_rgb(rgb[2], &error);
	if (error)
		return (mess_error("Invalid B value"));
	return (0);
}

int	extract_color(t_data *data, char *line, char type)
{
	char	**color;
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	while (line[i] == type || ft_isspace(line[i]))
		i++;
	color = ft_split(&line[i], ',');
	if (!color || !color[0] || !color[1] || !color[2])
		return (free_split(color), mess_error("Invalid RGB format"));
	if (color[3])
		return (free_split(color), mess_error("Too many RGB values"));
	if (parse_rgb(color, &r, &g, &b))
		return (free_split(color), 1);
	free_split(color);
	if (type == 'F')
		data->floor_color = create_rgb(r, g, b);
	else
		data->ceiling_color = create_rgb(r, g, b);
	return (0);
}

int	parse_color(t_data *data, char *line, char type)
{
	if (type == 'F' && data->floor_color != -1)
		return (mess_error("Duplicate floor color"));
	if (type == 'C' && data->ceiling_color != -1)
		return (mess_error("Duplicate ceiling color"));
	return (extract_color(data, line, type));
}
