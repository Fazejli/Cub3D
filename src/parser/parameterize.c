/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameterize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:24 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/26 13:24:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "utils/error.h"
#include "gfx/gfx.h"

typedef struct s_params
{
	t_image		*textures[4];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_error		error;
}	t_params;

typedef struct s_p_addr
{
	const char	*north_wall;
	const char	*south_wall;
	const char	*west_wall;
	const char	*east_wall;
	const char	*floor_color;
	const char	*ceiling_color;
	t_error		error;
}				t_p_addr;

static char	*get_address(const char *data, size_t size, const char *key)
{
	char	*ret;

	ret = memmem(data, size, key, strlen(key) + 1);
	if (!ret)
		return (NULL);
	if (ret == data && ret[-1] != '\n')
		return (NULL);
	return (ret + strlen(key));
}

static t_p_addr	validate_params(const char *data)
{
	t_p_addr	p;
	size_t		size;

	if (!data)
		return ((t_p_addr){.error = ERR_UNKNOWN}); //error to be added
	size = strlen(data);
	p.north_wall = get_address(data, size, "NO ");
	p.south_wall = get_address(data, size, "SO ");
	p.west_wall = get_address(data, size, "WE ");
	p.east_wall = get_address(data, size, "EA ");
	p.floor_color = get_address(data, size, "F ");
	p.ceiling_color = get_address(data, size, "C ");
	if (!p.north_wall || !p.south_wall || !p.west_wall || !p.east_wall
		|| !p.floor_color || !p.ceiling_color)
		return ((t_p_addr){.error = ERR_UNKNOWN}); //error to be added
	return (p);
}

static t_image	*get_texture(void *mlx, const char *path)
{
	t_image	*tex;
	char	*str;
	size_t	len;

	if (!path)
		return (NULL);
	len = 0;
	while (path[len] && path[len] != '\n')
		len++;
	str = strndup(path, len);
	if (!str)
		return (NULL);
	tex = get_image_from_xpm(mlx, str);
	free(str);
	return (tex);

}

void	free_params(void *mlx, t_params *params)
{
	size_t	i;

	if (!params)
		return ;
	i = 0;
	while (i < 4)
	{
		if (params->textures[i])
			free_image(mlx, params->textures[i]);
		i++;
	}
	memset(params, 0, sizeof(t_params));
}

uint32_t	get_color(const char *path)
{
	int			r;
	int			g;
	int			b;

	if (!path)
		return (0);
	while (*path && *path != '\n' && *path != ',')
		path++;
	while (*path && *path != '\n' && *path == ',')
		path++;
	r = atoi(path);
	while (*path && *path != '\n' && *path != ',')
		path++;
	while (*path && *path != '\n' && *path == ',')
		path++;
	g = atoi(path);
	while (*path && *path != '\n' && *path != ',')
		path++;
	while (*path && *path != '\n' && *path == ',')
		path++;
	b = atoi(path);
	return (r << 16 | g << 8 | b);
}

t_params	parameterize_file(void *mlx, const char *data)
{
	t_p_addr	p;
	t_params	params;

	p = validate_params(data);
	if (p.error)
		return ((t_params){.error = p.error});
	params.textures[0] = get_texture(mlx, p.north_wall);
	params.textures[1] = get_texture(mlx, p.south_wall);
	params.textures[2] = get_texture(mlx, p.west_wall);
	params.textures[3] = get_texture(mlx, p.east_wall);
	if (!params.textures[0] || !params.textures[1]
		|| !params.textures[2] || !params.textures[3])
	{
		free_params(mlx, &params);
		return (t_params){.error = ERR_BAD_TEXTURE}; //error to be added
	}
	params.floor_color = get_color(p.floor_color);
	params.ceiling_color = get_color(p.ceiling_color);
	return (params);
}
