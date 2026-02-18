/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:10:38 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 23:54:39 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>

# include "cub3d.h"
# include <stdatomic.h>
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

typedef struct s_gfx {
	void	*mlx;
	void	*win;
}	t_gfx;

typedef union u_keys {
	struct s_values {
		bool	forward : 1;
		bool	backward : 1;
		bool	left : 1;
		bool	right : 1;
		bool	up : 1;
		bool	down : 1;
		bool	yaw_left : 1;
		bool	yaw_right : 1;
		bool	pitch_up : 1;
		bool	pitch_down : 1;

		int32_t	reserved : 22;
	}	values;
	uint32_t	bits;
}	t_keys;

typedef struct s_input {
	t_keys	keys;
}	t_input;

typedef struct s_game
{
	t_data		*data;
	void		*mlx;
	void		*win;
	void		*img;
	uint32_t	*addr;
	t_gfx		gfx;
	t_input		input;
	t_player	player;
	t_options	opt;
	int			bpp;
	int			endian;
	int			size_len;
	int			texture_count;
	t_texture	textures[4];
}	t_game;

void		game_destroy(t_game *game, int exit_code)
			__attribute__((noreturn));

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

int			hooks_init(t_game *game);

#endif
