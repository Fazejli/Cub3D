/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 14:54:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include "parser.h"
# include <stdint.h>

# if defined(__linux__)
#  include <X11/X.h>
#  include <X11/keysym.h>

static const int	g_destroy_notify = DestroyNotify;
static const int	g_button_press = ButtonPress;
static const int	g_button_press_mask = ButtonPressMask;
static const int	g_key_press = KeyPress;
static const int	g_key_press_mask = KeyPressMask;
static const int	g_key_release = KeyRelease;
static const int	g_key_release_mask = KeyReleaseMask;

static const int	g_key_w = XK_w;
static const int	g_key_s = XK_s;
static const int	g_key_a = XK_a;
static const int	g_key_d = XK_d;
static const int	g_key_space = XK_space;
static const int	g_key_c = XK_c;
static const int	g_key_left = XK_Left;
static const int	g_key_right = XK_Right;
static const int	g_key_up = XK_Up;
static const int	g_key_down = XK_Down;
# elif defined(__APPLE__)

static const int	g_destroy_notify = 17;
static const int	g_button_press = 4;
static const int	g_button_press_mask = 1L << 2;
static const int	g_key_press = 2;
static const int	g_key_press_mask = 1L << 0;
static const int	g_key_release = 3;
static const int	g_key_release_mask = 1L << 1;

static const int	g_key_w = 13;
static const int	g_key_s = 1;
static const int	g_key_a = 0;
static const int	g_key_d = 2;
static const int	g_key_space = 49;
static const int	g_key_c = 8;
static const int	g_key_left = 123;
static const int	g_key_right = 124;
static const int	g_key_up = 126;
static const int	g_key_down = 125;
# endif

enum e_dir {
	EAST,
	NORTH,
	WEST,
	SOUTH,
};

typedef struct s_pos
{
	float		x;
	float		y;
	enum e_dir	dir;
}	t_pos;

typedef struct s_data
{
	char		*t_north;
	char		*t_south;
	char		*t_west;
	char		*t_east;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	char		**map;
	t_pos		player_pos;
	int			fd;
}	t_data;

typedef enum e_render_mode : uint8_t {
	RENDER_DDA,
}	t_render_mode;

typedef struct s_options {
	t_render_mode	mode;
	char			reserved[1];
	int16_t			thread_count;
}	t_options;

/*  Utils   */
int		check_arg(const char *filename);
int		mess_error(const char *msg);

int		options_init(t_options *opt, int argc, char **argv);

/* Cleanup  */
void	free_data(t_data *data);
void	free_map_and_player(t_data *data);
void	free_map(char **map);

#endif
