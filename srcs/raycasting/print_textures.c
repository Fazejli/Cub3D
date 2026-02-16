#include "cub3d.h"

t_texture	*get_texture(t_ray *ray, t_game *game)
{
	if (ray->side == EAST || ray->side == WEST)
	{
		if (ray->dir.x > 0)
			return (&game->textures[3]);
		else
			return (&game->textures[2]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&game->textures[1]);
		else
			return (&game->textures[0]);
	}
}
