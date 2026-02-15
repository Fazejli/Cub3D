#include "cub3d.h"

static void find_wall(t_ray *ray, char **map)
{
    int wall;

    wall = 0;
    while (!wall)
    {
        if (ray->dda.side_x < ray->dda.side_y)
        {
            ray->dda.side_x += ray->dda.delta_x;
            ray->pos_x += ray->dda.step_x;
            ray->side = 0;
        }
        else
        {
            ray->dda.side_y += ray->dda.delta_y;
            ray->pos_y += ray->dda.step_y;
            ray->side = 1;
        }
        if (ray->pos_y < 0 || ray->pos_y >= get_height(map))
            wall = 1;
        else if (ray->pos_x < 0 || ray->pos_x >= (int)ft_strlen(map[ray->pos_y]))
            wall = 1;
        else if (!wall && map[ray->pos_y][ray->pos_x] == '1')
            wall = 1;
    }
    calculate_distances(ray);
}

static void init_algo(t_ray *ray, t_player *player)
{
    ray->dda.delta_x = 1e30;
    if (ray->dir.x != 0)
    {
        ray->dda.delta_x = fabs(1.0 / ray->dir.x);
        if (ray->dir.x < 0)
        {
            ray->dda.step_x = -1;
            ray->dda.side_x = (player->pos.x - ray->pos_x) * ray->dda.delta_x;
        }
        else
        {
            ray->dda.step_x = 1;
            ray->dda.side_x = (ray->pos_x + 1.0 - player->pos.x) * ray->dda.delta_x;
        }
    }
    ray->dda.delta_y = 1e30;
    if (ray->dir.y != 0)
    {
        ray->dda.delta_y = fabs(1.0 / ray->dir.y);
        if (ray->dir.y < 0)
        {
            ray->dda.step_y = -1;
            ray->dda.side_y = (player->pos.y - ray->pos_y) * ray->dda.delta_y;
        }
        else
        {
            ray->dda.step_y = 1;
            ray->dda.side_y = (ray->pos_y + 1.0 - player->pos.y) * ray->dda.delta_y;
        }
    }
}

static void init_ray(t_ray *ray, t_player *player, int x)
{
    double cam;

    if (x < 0 || x >= WIDTH)
        return ;
    cam = 2.0 * x / (float)WIDTH - 1.0;
    ray->dir.x = player->dir.x + cam * player->plane.x;
    ray->dir.y = player->dir.y + cam * player->plane.y;
    ray->pos_x = (int)player->pos.x;
    ray->pos_y = (int)player->pos.y;
}

void raycast(t_game *game)
{
	t_ray   ray;
    int     x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &game->player, x);
        init_algo(&ray, &game->player);
        find_wall(&ray, game->data->map);
        //Afficher les rayons
        x++;
	}
}
