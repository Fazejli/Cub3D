/* ========== inc/game.h ========== */
#ifndef GAME_H
# define GAME_H

# include "cub3d.h"
# include <math.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_SIZE 64
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		tex[4];
	t_data		*data;
	t_player	player;
	t_keys		keys;
}	t_game;

/* Game initialization */
int		init_game(t_game *game, t_data *data);
void	init_player(t_game *game);
int		load_textures(t_game *game);

/* Raycasting */
void	raycasting(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_height(t_ray *ray);
void	draw_vertical_line(t_game *game, t_ray *ray, int x);

/* Rendering */
void	render_frame(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_texture_color(t_img *tex, int x, int y);

/* Events */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		handle_close(t_game *game);
int		game_loop(t_game *game);

/* Movement */
void	update_player(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

/* Utils */
void	free_game(t_game *game);
int		is_wall(t_game *game, int x, int y);

#endif
