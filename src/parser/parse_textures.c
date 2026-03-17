/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:30:34 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/17 12:15:24 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utils/t_str.h"

#include "parser_internal.h"

#include <stdio.h>

#define PATH_SIZE 256

static int	add_tile_texture(t_assets *a, t_str key, t_str option, t_str path)
{
	char			buf[PATH_SIZE];
	t_tile			*tile;
	uint32_t		dir;

	tile = &a->tiles[(unsigned char)key.ptr[0] - 32];
	if (!tile->flags)
		return (dprintf(2, "Textures: tile '%c' has not been initialized\n", *key.ptr), 1);
	dir = parse_dir_option(option);
	if (dir >= DIR_COUNT || dir == DIR_INVALID)
		return (dprintf(2, "Textures: orientation not valid: [%.*s]\n", (int)option.len, option.ptr), 1);
	if (tile->textures[dir] != NULL)
		return (dprintf(2, "Textures: texture for tile '%c' already has previous attribution\n", *key.ptr), 1);
	if (path.len >= sizeof(buf))
		return (dprintf(2, "Textures: path too long: [...%.*s]\n", 13, &path.ptr[path.len - 13]), 1);
	memcpy(buf, path.ptr, path.len);
	buf[path.len] = '\0';
	tile->textures[dir] = get_image_from_xpm(a->gfx->mlx, buf);
	if (tile->textures[dir] == NULL)
		return (dprintf(2, "Textures: could not load texture: [%.*s]\n", (int)path.len, path.ptr), 1);
	return (0);
}

static int	add_asset_texture(t_assets *a, t_str key, t_str option, t_str path)
{
	(void)option; //asset textures do not support options yet

	char	buf[PATH_SIZE];
	t_image **tex;

	if (key.len < 2)
		return (dprintf(2, "Textures: key not valid: [%.*s]\n", (int)key.len, key.ptr), 1);
	if (key.len == 7 && strncmp(key.ptr, "invalid", 7) == 0)
		tex = &a->invalid;
	else if (key.len == 6 && strncmp(key.ptr, "skybox", 6) == 0)
		tex = &a->skybox;
	else
		return (dprintf(2, "Textures: could not find valid texture address: [%.*s]\n", (int)key.len, key.ptr), 1);
	if (*tex != NULL)
		return (dprintf(2, "Textures: texture for asset '%.*s' already has previous attribution.\n", (int)key.len, key.ptr), 1);
	if (path.len >= sizeof(buf))
		return (dprintf(2, "Textures: path too long: [...%.*s]\n", 13, &path.ptr[path.len - 13]), 1);
	memcpy(buf, path.ptr, path.len);
	buf[path.len] = '\0';
	*tex = get_image_from_xpm(a->gfx->mlx, buf);
	if (*tex == NULL)
		return (dprintf(2, "Textures: could not load texture\'n"), 1);
	return (0);
}

int	parse_textures(t_assets *a, t_parser p)
{
	t_str		line;
	t_str		key;
	t_str		option;
	t_str		path;
	int			status;

	while (next_line(&p, &line, true, true))
	{
		if (line.len == 0)
			continue ;
		if (!split_key_value(line, &key, &path))
			return (dprintf(2, "Textures: could not find seperate key and value: [%.*s]\n", (int)line.len, line.ptr), 1);
		if (key.len == 0 || path.len == 0)
			return (dprintf(2, "Textures: no path or key specified'.\n"), 1);
		split_key_option(key, &key, &option);
		if (is_tile_key(key))
			status = add_tile_texture(a, key, option, path);
		else
			status = add_asset_texture(a, key, option, path);
		if (status)
			return (status);
	}
	return (0);
}
