#include "cub3d.h"

int load_texture(t_game *game, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
        return (mess_error("Failed to load texture"));
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_len, &tex->endian);
    return (0);
}

static void calculate_wall_height(t_ray *ray)
{
    ray->line_height = HEIGHT / ray->dist;
    ray->draw_start = (HEIGHT - ray->line_height) / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->draw_start + ray->line_height;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

void calculate_distances(t_ray *ray)
{
    if (ray->side == 0)
        ray->dist = ray->dda.side_x - ray->dda.delta_x;
    else
        ray->dist = ray->dda.side_y - ray->dda.delta_y;
    calculate_wall_height(ray);
}

