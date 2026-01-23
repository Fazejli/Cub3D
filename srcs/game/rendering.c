
/* ========== srcs/game/rendering.c ========== */
#include "../../inc/game.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static int	get_tex_index(t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (3);
	if (ray->side == 0 && ray->step_x < 0)
		return (2);
	if (ray->side == 1 && ray->step_y > 0)
		return (1);
	return (0);
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		tex_index;
	double	wall_x;
	double	step;
	double	tex_pos;

	tex_index = get_tex_index(ray);
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)game->tex[tex_index].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = game->tex[tex_index].width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = game->tex[tex_index].width - tex_x - 1;
	step = 1.0 * game->tex[tex_index].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = 0;
	while (y < ray->draw_start)
		my_mlx_pixel_put(&game->img, x, y++, game->data->ceiling_color);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->tex[tex_index].height - 1);
		tex_pos += step;
		my_mlx_pixel_put(&game->img, x, y,
			get_texture_color(&game->tex[tex_index], tex_x, tex_y));
		y++;
	}
	while (y < WIN_HEIGHT)
		my_mlx_pixel_put(&game->img, x, y++, game->data->floor_color);
}

void	render_frame(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}