/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:10:38 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/14 17:02:37 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "cub3d.h"

#define WIDTH 680
#define HEIGHT 680



typedef struct s_vec 
{
	float x;
	float y;
}	t_vec;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	cam;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	int			bpp;
	int			endian;
	int			size_len;
	t_data		*data;
	t_player	player;
}	t_game;

int		init_game(t_game *game, t_data *data);

#endif
