#include "inc/cub3d.h"

void draw_map(t_game *game)
{

}

int init_game(t_game *game, t_data *data)
{
	game->data = data;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_data(data), 1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		return (free_data(data), 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (free_data(data), 1);
	draw_map(game);

	return (0);
}