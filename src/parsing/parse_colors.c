/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:09:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdint.h>

uint32_t	create_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return ((uint32_t)(r << 16u) | (uint32_t)(g << 8u) | b);
}

int	parse_rgb(char **rgb, uint8_t *r, uint8_t *g, uint8_t *b)
{
	int	error;

	*r = (uint8_t)ft_atoi_rgb(rgb[0], &error);
	if (error)
		return (mess_error("Invalid R value"));
	*g = (uint8_t)ft_atoi_rgb(rgb[1], &error);
	if (error)
		return (mess_error("Invalid G value"));
	*b = (uint8_t)ft_atoi_rgb(rgb[2], &error);
	if (error)
		return (mess_error("Invalid B value"));
	return (0);
}

int	extract_color(t_data *data, char *line, char type)
{
	char	**color;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
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
	if (type == 'F' && data->floor_color != -1u)
		return (mess_error("Duplicate floor color"));
	if (type == 'C' && data->ceiling_color != -1u)
		return (mess_error("Duplicate ceiling color"));
	return (extract_color(data, line, type));
}
