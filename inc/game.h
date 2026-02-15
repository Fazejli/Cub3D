/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:10:38 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/15 03:49:16 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "cub3d.h"

#define WIDTH 680
#define HEIGHT 680

#define KEY_PRESS 2
#define KEY_RELEASE 3
#define DESTROY_NOTIFY 17

typedef struct s_vector 
{
	double x;
	double y;
}	t_vector;

typedef struct s_algo
{
	double delta_x;
	double delta_y;
	double side_x;
	double side_y;
	int step_x;
	int step_y;
}	t_algo;

typedef struct s_ray
{
	t_vector	dir;
	int		pos_x;
	int		pos_y;
	double	dist;
	int		line_height;
	int		side;
	t_algo	dda;
    int		draw_start;    // Début de la ligne
    int		draw_end;		// Fin de la ligne
} t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
	int     height;
    int     bpp;
    int     size_len;
    int		endian;
}   t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			endian;
	int			size_len;
	t_data		*data;
	t_texture	textures[4];
	t_player	player;
}	t_game;

int		init_game(t_game *game, t_data *data);
int		load_texture(t_game *game, t_texture *tex, char *path);
void	raycast(t_game *game);
void	calculate_distances(t_ray *ray);

int		quit_game(t_game *game);
int		key_press(int key_code, t_game *game);

#endif

//Pour chaque rayon : direction, distance au mur, coordonnées de collision
//Pour le dessin : hauteur du mur à l'écran, position de la texture
