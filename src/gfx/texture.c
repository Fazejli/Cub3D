/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:15:39 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/24 18:40:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdint.h>

static int	load_texture(t_game *g, char *name, int index)
{
	uint32_t	width;
	uint32_t	height;
	void		*image;

	if (!name)
	{
		// todo missing texture error
		return (1);
	}
	image = mlx_xpm_file_to_image(g->mlx, name, &width, &height);
	if (!image)
	{
		// todo load fail error
		return (1);
	}
	g->textures[index] = image;
	return (0);
}

int	load_textures(t_game *g)
{
	uint32_t	i;
	bool		error;

	error = 0;
	i = 0;
	while (i < g->gfx.texture_count)
	{
		error |= load_texture(g, tex_file, i);
		i++;
	}
	return (error);
}
