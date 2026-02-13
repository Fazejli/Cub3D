/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:10:38 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/13 10:57:19 by fadzejli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "cub3d.h"

#define WIDTH 680
#define HEIGHT 680



typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	int			bpp;
	int			endian;
	int			size_len;
	t_data		*data;
}	t_game;

int init_game(t_game *game, t_data *data);

#endif