/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/18 13:04:04 by smamalig         ###   ########.fr       */
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

constexpr int	g_destroy_notify = DestroyNotify;
constexpr int	g_button_press = ButtonPress;
constexpr int	g_button_press_mask = ButtonPressMask;
constexpr int	g_key_press = KeyPress;
constexpr int	g_key_press_mask = KeyPressMask;
constexpr int	g_key_release = KeyRelease;
constexpr int	g_key_release_mask = KeyReleaseMask;

constexpr int	g_key_w = XK_w;
constexpr int	g_key_s = XK_s;
constexpr int	g_key_a = XK_a;
constexpr int	g_key_d = XK_d;
constexpr int	g_key_space = XK_space;
constexpr int	g_key_c = XK_c;
constexpr int	g_key_left = XK_Left;
constexpr int	g_key_right = XK_Right;
constexpr int	g_key_up = XK_Up;
constexpr int	g_key_down = XK_Down;
# elif defined(__APPLE__)

constexpr int	g_destroy_notify = 17;
constexpr int	g_button_press = 4;
constexpr int	g_button_press_mask = 1L << 2;
constexpr int	g_key_press = 2;
constexpr int	g_key_press_mask = 1L << 0;
constexpr int	g_key_release = 3;
constexpr int	g_key_release_mask = 1L << 1;

constexpr int	g_key_w = 13;
constexpr int	g_key_s = 1;
constexpr int	g_key_a = 0;
constexpr int	g_key_d = 2;
constexpr int	g_key_space = 49;
constexpr int	g_key_c = 8;
constexpr int	g_key_left = 123;
constexpr int	g_key_right = 124;
constexpr int	g_key_up = 126;
constexpr int	g_key_down = 125;
# endif

enum e_dir : uint8_t {
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

	char		reserved[3];
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

/*  Utils   */
int		check_arg(const char *filename);
int		mess_error(const char *msg);

/* Cleanup  */
void	free_data(t_data *data);
void	free_map_and_player(t_data *data);
void	free_map(char **map);

#endif
