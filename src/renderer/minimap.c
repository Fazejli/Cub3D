/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:20:56 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/21 12:32:53 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>
#include "assets/assets.h"
#include "gfx/gfx.h"
#include "world/world.h"

#define MM_SIZE		128
#define MM_RADIUS	2.5f
#define MM_OFFSET	10
#define MM_WALL		0x00FFFFFF
#define MM_FLOOR	0x00333333
#define MM_PLAYER	0x00FF0000
#define MM_OOB		0x00111111

static uint32_t	get_tile_color(const t_map *map, const t_tile *tiles,
					int tx, int ty)
{
	uint32_t	tile_id;

	if (tx < 0 || tx >= (int)map->width
		|| ty < 0 || ty >= (int)map->height)
		return (MM_OOB);
	tile_id = map->data[ty * map->width + tx];
	if (tiles[tile_id].flags & TILE_F_RAY_BLOCK)
		return (MM_WALL);
	return (MM_FLOOR);
}

static void	draw_player_dot(t_image *frame, uint32_t cx, uint32_t cy)
{
	int	dx;
	int	dy;

	dy = -4;
	while (dy <= 4)
	{
		dx = -4;
		while (dx <= 4)
		{
			if (dx * dx + dy * dy <= 16)
				set_pixel(cx + dx, cy + dy, MM_PLAYER, frame);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_image *f, const t_world *w, const t_assets *a)
{
	uint32_t	px;
	uint32_t	py;
	float		world_x;
	float		world_y;

	py = 0;
	while (py < MM_SIZE)
	{
		px = 0;
		while (px < MM_SIZE)
		{
			world_x = w->player.pos.x
				+ ((float)px / MM_SIZE - 0.5f) * (MM_RADIUS * 2);
			world_y = w->player.pos.y
				+ ((float)py / MM_SIZE - 0.5f) * (MM_RADIUS * 2);
			set_pixel(MM_OFFSET + px, MM_OFFSET + py,
				get_tile_color(&a->map, a->tiles,
					(int)floorf(world_x), (int)floorf(world_y)),
				f);
			px++;
		}
		py++;
	}
	draw_player_dot(f, MM_OFFSET + MM_SIZE / 2,
		MM_OFFSET + MM_SIZE / 2);
}
