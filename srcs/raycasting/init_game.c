#include "cub3d.h"

static void init_vector(t_vector *vector, double x_nbr, double y_nbr)
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
		init_vector(&player->plane, 0.66, 0);
	}
	else if (pos->pos == 'S')
    {
        init_vector(&player->dir, 0, 1);
		init_vector(&player->plane, -0.66, 0);
	}
	else if (pos->pos == 'W')
    {
        init_vector(&player->dir, -1, 0);
		init_vector(&player->plane, 0, 0.66);
	}
	else if (pos->pos == 'E')
    {
        init_vector(&player->dir, 1, 0);
		init_vector(&player->plane, 0, -0.66);
	}
}

static int load_textures(t_game *game, t_data *data)
{
	if (load_texture(game, &game->textures[0], data->t_north))
        return (free_data(data),1);
    if (load_texture(game, &game->textures[1], data->t_south))
        return (free_data(data),1);
    if (load_texture(game, &game->textures[2], data->t_west))
        return (free_data(data),1);
    if (load_texture(game, &game->textures[3], data->t_east))
        return (free_data(data),1);
	return (0);
}

int init_game(t_game *game, t_data *data)
{
	game->data = data;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_data(data), 1);
	if (load_textures(game, data))
		return (1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		return (free_data(data), 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (free_data(data), 1);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_len, &game->endian);
	init_player(&game->player, data->player_pos);
	raycast(game);
	mlx_hook(game->win, DESTROY_NOTIFY, 0, quit_game, game);
	mlx_key_hook(game->win, key_press, game);
	return (0);
}
