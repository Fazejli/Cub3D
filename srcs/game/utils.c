
/* ========== srcs/game/utils.c ========== */
#include "../../inc/game.h"

int	is_wall(t_game *game, int x, int y)
{
	if (y < 0 || y >= get_height(game->data->map))
		return (1);
	if (x < 0 || x >= (int)ft_strlen(game->data->map[y]))
		return (1);
	if (game->data->map[y][x] == '1')
		return (1);
	return (0);
}

void	free_game(t_game *game)
{
	int	i;

	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}