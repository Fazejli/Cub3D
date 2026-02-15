#include "cub3d.h"

int key_press(int key_code, t_game *game)
{
    if (key_code == 53 || key_code == 65307)
        quit_game(game);
    return (0);
}

int quit_game(t_game *game)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
        i++;
    }
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    free_data(game->data);
    exit(0);
    return (0);
}
