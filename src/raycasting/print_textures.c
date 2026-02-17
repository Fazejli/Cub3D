#include "cub3d.h"

int	get_color(t_texture *tex)
{
	int	offset;
	int	color;

	offset = tex->y * tex->size_len + tex->x * (tex->bpp / 8);
	color = *(int *)(tex->addr + offset);
	return (color);
}


int	check_pos(float pos, t_texture *tex)
{
	if (pos < 0)
		return (0);
	else if (pos >= tex->height)
		return (tex->height - 1);
	return ((int)pos);
}

float	find_intersection(t_ray *ray, t_player player)
{
	float	wall;

	if (ray->side == EAST || ray->side == WEST)
		wall = player.pos.y + ray->dist * ray->dir.y;
	else
		wall = player.pos.x + ray->dist * ray->dir.x;
	wall = wall - (int)wall;
	return (wall);
}

t_texture	*get_texture(t_ray *ray, t_game *game)
{
	if (ray->side == EAST || ray->side == WEST)
	{
		if (ray->dir.x > 0)
			return (&game->textures[EAST]);
		else
			return (&game->textures[WEST]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->textures[NORTH]);
		else
			return (&game->textures[SOUTH]);
	}
}
