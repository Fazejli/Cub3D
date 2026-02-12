/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:28:35 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/12 12:28:41 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map_and_player(t_data *data)
{
	if (data->map)
	{
		free_map(data->map);
		data->map = NULL;
	}
	if (data->player_pos)
	{
		free(data->player_pos);
		data->player_pos = NULL;
	}
}

void	free_textures(t_data *data)
{
	if (data->t_north)
	{
		free(data->t_north);
		data->t_north = NULL;
	}
	if (data->t_south)
	{
		free(data->t_south);
		data->t_south = NULL;
	}
	if (data->t_west)
	{
		free(data->t_west);
		data->t_west = NULL;
	}
	if (data->t_east)
	{
		free(data->t_east);
		data->t_east = NULL;
	}
}

void	free_data(t_data *data)
{
	free_textures(data);
	free_map_and_player(data);
	if (data->fd > 0)
	{
		close(data->fd);
		data->fd = 0;
	}
}
