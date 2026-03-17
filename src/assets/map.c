/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:44:57 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 19:48:56 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

#include "assets/assets.h"

t_tile	*map_tile_at(t_assets *assets, size_t x, size_t y)
{
	if (x >= assets->map.width || y >= assets->map.height)
		return (NULL);
	return (&assets->tiles[assets->map.data[y * assets->map.width + x]]);
}
