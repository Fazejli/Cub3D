#include "inc/game.h"

void init_game(t_game *game, t_data *data)
{
	game->mlx = (void *)NULL;
	game->data = data;
	game->win = (void *)NULL;
}