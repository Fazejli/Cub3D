/* ========== srcs/game/init_game.c ========== */
#include "../../inc/game.h"

int	init_game(t_game *game, t_data *data)
{
	game->data = data;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (mess_error("MLX init failed"));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (mess_error("Window creation failed"));
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		return (mess_error("Image creation failed"));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	ft_memset(&game->keys, 0, sizeof(t_keys));
	init_player(game);
	if (load_textures(game))
		return (1);
	return (0);
}

void	init_player(t_game *game)
{
	game->player.pos_x = game->data->player_pos->x + 0.5;
	game->player.pos_y = game->data->player_pos->y + 0.5;
	if (game->data->player_pos->pos == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->data->player_pos->pos == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->data->player_pos->pos == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->data->player_pos->pos == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

static int	load_single_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (mess_error("Texture loading failed"));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_single_texture(game, &game->tex[0], game->data->t_north))
		return (1);
	if (load_single_texture(game, &game->tex[1], game->data->t_south))
		return (1);
	if (load_single_texture(game, &game->tex[2], game->data->t_west))
		return (1);
	if (load_single_texture(game, &game->tex[3], game->data->t_east))
		return (1);
	return (0);
}