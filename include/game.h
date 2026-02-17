/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:10:38 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 00:23:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"
# include <stdint.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_algo
{
	float	delta_x;
	float	delta_y;
	float	side_x;
	float	side_y;
	int		step_x;
	int		step_y;
}	t_algo;

typedef struct s_ray
{
	t_vector	dir;
	int			pos_x;
	int			pos_y;
	float		dist;
	uint32_t	line_height;
	int			side;
	t_algo		dda;
	uint32_t	start;
	uint32_t	end;
}	t_ray;

typedef struct s_player
{
	t_vector	pos;
	float		yaw;
	float		fov;
}	t_player;

typedef struct s_texture
{
	void		*img;
	uint32_t	*addr;
	uint32_t	width;
	uint32_t	height;
	uint32_t	bpp;
	uint32_t	size_len;
	uint32_t	endian;
	uint32_t	x;
	uint32_t	y;
	char		reserved[4];
}	t_texture;

typedef struct s_game
{
	t_data		*data;
	void		*mlx;
	void		*win;
	void		*img;
	uint32_t	*addr;
	int			bpp;
	int			endian;
	int			size_len;
	t_player	player;
	char		reserved[4];
	t_texture	textures[4];
}	t_game;

int			init_game(t_game *game, t_data *data);
int			load_texture(t_game *game, t_texture *tex, char *path);
void		raycast(t_game *game);
void		calculate_distances(t_ray *ray);
void		print_ray(t_ray *ray, t_game *game, uint32_t x);
t_texture	*get_texture(t_ray *ray, t_game *game);
uint32_t	check_pos(float pos, t_texture *tex);
uint32_t	get_color(t_texture *tex);	

float		find_intersection(t_ray *ray, t_player player);
int			quit_game(t_game *game);
int			key_press(int key_code, t_game *game);

#endif
