/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:29:47 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 12:30:09 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_separator(char *title)
{
	printf("\n========== %s ==========\n", title);
}

void	debug_textures(t_data *data)
{
	print_separator("TEXTURES");
	printf("North:   %s\n", data->t_north ? data->t_north : "NULL");
	printf("South:   %s\n", data->t_south ? data->t_south : "NULL");
	printf("West:    %s\n", data->t_west ? data->t_west : "NULL");
	printf("East:    %s\n", data->t_east ? data->t_east : "NULL");
}

void	debug_colors(t_data *data)
{
	int	r;
	int	g;
	int	b;

	print_separator("COLORS");
	if (data->floor_color != -1)
	{
		r = (data->floor_color >> 16) & 0xFF;
		g = (data->floor_color >> 8) & 0xFF;
		b = data->floor_color & 0xFF;
		printf("Floor:   RGB(%d, %d, %d) = 0x%06X\n", r, g, b, data->floor_color);
	}
	else
		printf("Floor:   NOT SET\n");
	if (data->ceiling_color != -1)
	{
		r = (data->ceiling_color >> 16) & 0xFF;
		g = (data->ceiling_color >> 8) & 0xFF;
		b = data->ceiling_color & 0xFF;
		printf("Ceiling: RGB(%d, %d, %d) = 0x%06X\n", r, g, b, data->ceiling_color);
	}
	else
		printf("Ceiling: NOT SET\n");
}

void	debug_player(t_data *data)
{
	print_separator("PLAYER");
	if (data->player_pos)
	{
		printf("Position: (%d, %d)\n", data->player_pos->x, data->player_pos->y);
		printf("Direction: %c\n", data->player_pos->pos);
	}
	else
		printf("Player: NOT FOUND\n");
}

void	debug_map(t_data *data)
{
	int	i;
	int	width;
	int	height;

	print_separator("MAP");
	if (!data->map)
	{
		printf("Map: NULL\n");
		return ;
	}
	height = get_height(data->map);
	width = get_width(data->map);
	printf("Dimensions: %d x %d\n", width, height);
	printf("Content:\n");
	i = 0;
	while (data->map[i])
	{
		printf("[%2d] %s", i, data->map[i]);
		if (data->map[i][ft_strlen(data->map[i]) - 1] != '\n')
			printf("\n");
		i++;
	}
}

void	debug_full(t_data *data)
{
	print_separator("CUB3D DEBUG REPORT");
	debug_textures(data);
	debug_colors(data);
	debug_player(data);
	debug_map(data);
	print_separator("END OF REPORT");
}
