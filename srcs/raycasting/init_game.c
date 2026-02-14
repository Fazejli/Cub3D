#include "cub3d.h"

static void init_vector(t_vec *vector, float x_nbr, float y_nbr)
{
    vector->x = x_nbr;
    vector->y = y_nbr;
}

static void init_player(t_player *player, t_pos *pos)
{
	init_vector(&player->pos, pos->x + 0.5, pos->y + 0.5);
	if (pos->pos == 'N')
    {
        init_vector(&player->dir, 0, -1);
		init_vector(&player->cam, 0.66, 0);
	}
	else if (pos->pos == 'S')
    {
        init_vector(&player->dir, 0, 1);
		init_vector(&player->cam, -0.66, 0);
	}
	else if (pos->pos == 'W')
    {
        init_vector(&player->dir, -1, 0);
		init_vector(&player->cam, 0, 0.66);
	}
	else if (pos->pos == 'E')
    {
        init_vector(&player->dir, 1, 0);
		init_vector(&player->cam, 0, -0.66);
	}
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
	init_player(&game->player, data->player_pos);
	debug_player(&game->player);
	//Raycasting
	return (0);
}