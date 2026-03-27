/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:56:20 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/24 17:20:03 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "world/world.h"

#include "renderer_internal.h"

static float	get_offset(const t_world *w, int32_t tx, int32_t ty)
{
	uint32_t	i;

	i = 0;
	while (i < w->entity_count)
	{
		if (w->entities[i].type == ENTITY_DOOR
			&& (int32_t)w->entities[i].pos.x == tx
			&& (int32_t)w->entities[i].pos.y == ty)
			return (w->entities[i].door.offset);
		i++;
	}
	return (0.0f);
}

static int	check_hit(t_ray *ray, t_hit *hit, t_render_task *task)
{
	const t_map		*map = &task->renderer->assets->map;
	const t_tile	*tiles = task->renderer->assets->tiles;

	hit->side = (ray->dda.side.x > ray->dda.side.y);
	ray->dda.side.e[hit->side] += ray->dda.delta.e[hit->side];
	ray->pos.e[hit->side] += (uint32_t)ray->dda.step.e[hit->side];
	if (ray->pos.x >= map->width || ray->pos.y >= map->height)
		return (-1);
	hit->tile_id = map->data[ray->pos.y * map->width + ray->pos.x];
	hit->offset = 0.0f;
	hit->is_door = false;
	if (tiles[hit->tile_id].flags & TILE_F_DOOR)
	{
		hit->offset = get_offset(task->world,
				(int32_t)ray->pos.x, (int32_t)ray->pos.y);
		if (hit->offset >= 1.0f)
			return (0);
		hit->is_door = true;
		return (1);
	}
	if (tiles[hit->tile_id].flags & TILE_F_RAY_BLOCK)
		return (1);
	return (0);
}

static void	calculate_distance(t_ray *ray, t_hit *hit, const t_player p)
{
	hit->dist = ((float)ray->pos.e[hit->side]
			- p.pos.e[hit->side]
			+ (float)(1 - ray->dda.step.e[hit->side]) * 0.5f)
		/ ray->dir.e[hit->side];
	if (hit->dist < 0.001f)
		hit->dist = 0.001f;
	hit->wall_x = p.pos.e[!hit->side] + hit->dist * ray->dir.e[!hit->side];
	hit->wall_x -= floorf(hit->wall_x);
}

void	init_ray(t_ray *ray, const t_player p, uint32_t width)
{
	const float		cam = 2.0f * (float)ray->x / (float)width - 1.0f;
	const t_vec2f	dir = {{cosf(p.yaw), sinf(p.yaw)}};
	const float		plane = tanf(p.fov * 0.5f);

	ray->dir.x = dir.x - dir.y * cam * plane;
	ray->dir.y = dir.y + dir.x * cam * plane;
	ray->pos.x = (uint32_t)p.pos.x;
	ray->pos.y = (uint32_t)p.pos.y;
	ray->dda.step.x = 1 - 2 * (ray->dir.x < 0);
	ray->dda.delta.x = fabsf(1.0f / ray->dir.x);
	ray->dda.side.x = ((ray->dir.x < 0) * (p.pos.x - (float)ray->pos.x)
			+ (ray->dir.x >= 0) * ((float)ray->pos.x + 1.0f - p.pos.x))
		* ray->dda.delta.x;
	ray->dda.step.y = 1 - 2 * (ray->dir.y < 0);
	ray->dda.delta.y = fabsf(1.0f / ray->dir.y);
	ray->dda.side.y = ((ray->dir.y < 0) * (p.pos.y - (float)ray->pos.y)
			+ (ray->dir.y >= 0) * ((float)ray->pos.y + 1.0f - p.pos.y))
		* ray->dda.delta.y;
}

int	cast_ray(t_ray *ray, t_hit *hit, t_render_task *task)
{
	int	result;

	hit->offset = 0.0f;
	hit->is_door = false;
	while (true)
	{
		result = check_hit(ray, hit, task);
		if (result != 0)
			break ;
	}
	if (result < 0)
		return (1);
	calculate_distance(ray, hit, task->world->player);
	return (0);
}
